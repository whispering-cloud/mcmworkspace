import time
import pandas as pd
import networkx as nx

# 数据路径
data_by_artist_src = "problem/2021_ICM_Problem_D_Data/data_by_artist.csv"
data_by_year_src = "problem/2021_ICM_Problem_D_Data/data_by_year.csv"
full_music_data_src = "problem/2021_ICM_Problem_D_Data/full_music_data.csv"
influence_data_src = "problem/2021_ICM_Problem_D_Data/influence_data.csv"

# 初始化
print("开始初始化")
_timer_start = time.time()

## 读入数据


def _read(info, src):
    try:
        print(info, end=': ')
        data = pd.read_csv(src)
    except Exception as err:
        print("读取失败！错误原因", err)
        exit()
    else:
        # print("读取成功，内容示例：")
        # print(data.head())
        print('读取成功！')
        return data


artist = _read("尝试读取艺术家信息", data_by_artist_src).set_index('artist_id',drop=False)
year = _read("尝试读取年份信息", data_by_year_src).set_index('year',drop=False)
music = _read("尝试读取音乐信息", full_music_data_src)
influence_data = _read(
    "尝试读取影响网络", influence_data_src).set_index('influencer_id',drop=False)

del _read

## 数据整理
music['release_date'] = pd.to_datetime(
    music['release_date'], infer_datetime_format=True)
music['artists_id'] = music['artists_id'].apply(eval)
music['artist_names'] = music['artist_names'].apply(eval)

_timer_end = time.time()
print("初始化完成，耗时：", _timer_end-_timer_start, "s")

# 构建影响网络

influence_network=nx.DiGraph()

influence_network.add_nodes_from(artist.index)
influence_network.add_edges_from([x for x in influence_data[['influencer_id','follower_id']].itertuples(index=False,name=None)])
