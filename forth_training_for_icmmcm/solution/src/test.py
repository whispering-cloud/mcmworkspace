import csv
import re
import time

# 数据路径
data_by_artist_src = "problem/2021_ICM_Problem_D_Data/data_by_artist.csv"
data_by_year_src = "problem/2021_ICM_Problem_D_Data/data_by_year.csv"
full_music_data_src = "problem/2021_ICM_Problem_D_Data/full_music_data.csv"
influence_data_src = "problem/2021_ICM_Problem_D_Data/influence_data.csv"

# 初始化，读取全部数据
print("开始初始化，读取数据")
_timer_start=time.time()

artist = dict()

with open(data_by_artist_src, encoding='utf-8') as csvfile:
    data_by_artist = csv.DictReader(csvfile)

    for record in data_by_artist:
        artist[record['artist_id']] = record
    del data_by_artist

year = dict()

with open(data_by_year_src, encoding='utf-8') as csvfile:
    data_by_year = csv.DictReader(csvfile)

    for record in data_by_year:
        artist[record['year']] = record
    del data_by_year


followers_to = dict()
for artist_id in artist.keys():
    artist[artist_id]['music_list']=list()
    followers_to[artist_id] = list()

with open(influence_data_src, encoding='utf-8') as csvfile:
    influence_data = csv.DictReader(csvfile)

    for record in influence_data:
        if record['influencer_id'] not in artist.keys() or record['follower_id'] not in artist.keys():
            continue
        followers_to[record['influencer_id']].append(record['follower_id'])
        artist[record['influencer_id']
               ]['main_genre'] = record['influencer_main_genre']
        artist[record['influencer_id']
               ]['active_start'] = record['influencer_active_start']
        artist[record['follower_id']
               ]['main_genre'] = record['follower_main_genre']
        artist[record['follower_id']
               ]['active_start'] = record['follower_active_start']
    del influence_data

music = dict()

with open(full_music_data_src, encoding='utf-8') as csvfile:
    music_data = csv.DictReader(csvfile)

    for record in music_data:
        record['artists_id']=re.findall(r"[-+]?\d*\.\d+|\d+",record['artists_id'])
        for artist_id in record['artists_id']:
            if not artist_id in artist.keys():
                continue
        record['artist_name']=[artist[x]['artist_name'] for x in record['artists_id']]
        music[record['song_title (censored)']]=record
        for artist_id in record['artists_id']:
            artist[artist_id]['music_list'].append(record['song_title (censored)'])
    del music_data

_timer_end=time.time()
print("读取数据完成，耗时：",_timer_end-_timer_start)

# 检查图中是否有环
print("检查图中是否有环")

def dfs(id,visited):
    if id in visited:
        print("卧槽真的有环！")
        print(visited)
        print("环环坏坏/(ㄒoㄒ)/~~")
        return True
    visited.add(id)
    for jd in followers_to[id]:
        if dfs(jd,visited.copy()):
            return True
    return False

for id in artist.keys():
    if dfs(id,set()):
        break
del dfs

# 计算节点影响力

