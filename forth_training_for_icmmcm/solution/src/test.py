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

# 读入数据
print("  开始读入数据")


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


artist = _read("    尝试读取艺术家信息", data_by_artist_src).set_index(
    'artist_id', drop=False)
year = _read("    尝试读取年份信息", data_by_year_src).set_index('year', drop=False)
music = _read("    尝试读取音乐信息", full_music_data_src)
influence_data = _read("    尝试读取影响网络", influence_data_src)

del _read
print("  读入数据完成")

# 整理数据
print("  开始整理数据")

music['release_date'] = pd.to_datetime(
    music['release_date'], infer_datetime_format=True)
music['artists_id'] = music['artists_id'].apply(eval)
music['artist_names'] = music['artist_names'].apply(eval)

print("  整理数据完成")

# 构建影响网络
print("  开始构建影响网络")

influence_network = nx.DiGraph()
for x in influence_data.itertuples():
    influence_network.add_node(x.influencer_id, name=x.influencer_name,
                               main_genre=x.influencer_main_genre, active_start=x.influencer_active_start)
    influence_network.add_node(x.follower_id, name=x.follower_name,
                               main_genre=x.follower_main_genre, active_start=x.follower_active_start)
influence_network.add_edges_from([x for x in influence_data[[
                                 'influencer_id', 'follower_id']].itertuples(index=False, name=None)])

del influence_data
print("  构建影响网络完成")

_timer_end = time.time()
print("初始化完成，耗时：", _timer_end-_timer_start, "s")

# 环检测
print("开始环检测")


def loop_check(id, visited=set()):
    if id in visited:
        print("  检测到环！环上节点集合：", visited)
        return True
    visited.add(id)
    for next in influence_network[id]:
        if loop_check(next, visited.copy()):
            return True
    return False


for node in influence_network.nodes:
    if loop_check(node):
        break
else:
    print("  未检测到环！")

del loop_check
print("环检测完成")

# 影响力计算
print("开始计算节点影响力")
_MAX_DEPTH = 4
_timer_start = time.time()


def influence(id, visited=set(), depth=0):
    if id in visited or depth >= _MAX_DEPTH:
        return 0
    visited.add(id)
    ret = 1
    for jd in influence_network[id]:
        ret += influence(jd, visited.copy(), depth+1)*0.5
    return ret


for node in influence_network.nodes:
    influence_network.nodes[node]['influence_coefficient'] = influence(node)

del influence, _MAX_DEPTH
_timer_end = time.time()
print("影响力计算完成，耗时：", _timer_end-_timer_start, "s")

# 相似度计算
print("开始计算艺术家相似度")
_timer_start = time.time()

print(len(artist.index))

_timer_end = time.time()
print("相似度计算完成，耗时：", _timer_end-_timer_start, "s")