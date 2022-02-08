import csv

# 数据路径
data_by_artist_src = r"C:\Users\fanya\Documents\华南理工大学\大一上\竞赛\数模\2021-ICM\2021_ICM_Problem_D_Data\data_by_artist.csv"
data_by_year_src = r"C:\Users\fanya\Documents\华南理工大学\大一上\竞赛\数模\2021-ICM\2021_ICM_Problem_D_Data\data_by_year.csv"
full_music_data_src = r"C:\Users\fanya\Documents\华南理工大学\大一上\竞赛\数模\2021-ICM\2021_ICM_Problem_D_Data\full_music_data.csv"
influence_data_src = r"C:\Users\fanya\Documents\华南理工大学\大一上\竞赛\数模\2021-ICM\2021_ICM_Problem_D_Data\influence_data.csv"

# problem_1

influence_map = dict()

with open(influence_data_src, encoding='utf-8') as csvfile:
    influence_data = csv.DictReader(csvfile)

    for record in influence_data:
        if not record['influencer_id'] in influence_map:
            influence_map[record['influencer_id']] = list()
        if not record['follower_id'] in influence_map:
            influence_map[record['follower_id']] = list()
        influence_map[record['influencer_id']].append(record['follower_id'])

# check DAG

followed_cnt = dict()

for id in influence_map:
    if not id in followed_cnt:
        followed_cnt[id] = 0
    for jd in influence_map[id]:
        if not jd in followed_cnt:
            followed_cnt[jd] = 0
        followed_cnt[jd] = followed_cnt[jd]+1

flag = True
while flag:
    flag = False
    for id in followed_cnt:
        if followed_cnt[id] == 0:
            flag = True
            for jd in influence_map[id]:
                if jd in followed_cnt:
                    followed_cnt[jd] = followed_cnt[jd]-1
            del followed_cnt[id]
            break

if len(followed_cnt) > 0:
    print("这不是无环图TAT，尝试找出环")

    def dfs(id, visited):
        if id in visited:
            print("找到环力："+str(visited))
            return True
        visited.add(id)
        ret = False
        for jd in influence_map[id]:
            ret = ret | dfs(jd, visited.copy())
            if ret:
                break
        return ret

    for id in influence_map:
        if dfs(id, set()):
            break
