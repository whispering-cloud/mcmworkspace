import csv

# 数据路径
data_by_artist_src = "problem/2021_ICM_Problem_D_Data/data_by_artist.csv"
data_by_year_src = "problem/2021_ICM_Problem_D_Data/data_by_year.csv"
full_music_data_src = "problem/2021_ICM_Problem_D_Data/full_music_data.csv"
influence_data_src = "problem/2021_ICM_Problem_D_Data/influence_data.csv"

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
