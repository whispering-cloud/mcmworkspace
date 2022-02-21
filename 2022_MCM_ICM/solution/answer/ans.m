dist=[0,8,27,53,76,87,96,108,125,149,169,187,213,245,268,289,313,332,345,362,388,420,448,479,511,543,575,607,634,660,679,691,702,717,741,772,795,815,838,858,877,900,925,942,955,963,970,976,989,1012,1032,1046,1051,1053,1054,1056,1063,1080,1102,1128,1150,1160,1168,1185,1205,1224,1243,1262,1279,1291,1302,1318,1338,1362,1390,1422,1450,1476,1496,1509,1520,1531,1546,1564,1581,1596,1610,1625,1645,1668,1689,1711,1736,1758,1778,1802,1833,1861,1885,1911,1939,1969,1996,2015,2022,2028,2043,2066,2091,2113,2138,2169,2197,2217,2230,2241,2256,2280,2306,2329,2355,2382,2405,2426,2445,2462,2480,2504,2532,2559,2582,2607,2632,2648,2658,2668,2683,2707,2731,2755,2785,2813,2838,2860,2884,2911,2938,2967,2990,3004,3010,3017,3034,3051,3068,3093,3115,3135,3163,3186,3202,3222,3247,3275,3304,3331,3360,3387,3411,3433,3453,3471,3493,3522,3545,3556,3568,3590,3619,3647,3666,3677,3686,3695,3703,3715,3736,3764,3792,3816,3837,3857,3878,3900,3924,3956,3983,4009,4035,4053,4060,4071,4087,4095,4098,4109,4134,4163,4194,4222,4247,4270,4291,4312];
x=1:214;
da=[380,280,190,260,340,410,320,220,220,120,20,1,61,201,201,271,371,451,401,361,301,201,101,1,1,1,1,41,1,1,31,51,1,1,1,131,121,151,231,291,201,141,171,111,191,211,301,301,201,121,21,1,11,171,181,281,341,441,341,371,431,421,381,291,201,101,21,21,1,1,101,1,1,1,1,191,291,231,291,231,311,271,181,181,81,31,1,41,1,1,201,301,401,491,461,411,371,331,301,221,131,101,1,1,111,11,1,81,71,201,241,341,391,291,191,91,111,11,1,1,1,1,1,1,1,111,211,171,91,101,61,201,151,251,281,351,451,411,471,411,371,331,231,251,151,111,11,1,71,201,301,261,171,261,161,61,1,1,181,81,41,11,1,201,301,291,201,291,371,281,331,311,281,261,241,221,221,181,141,71,101,171,211,141,181,81,1,1,11,1,1,1,91,31,171,71,101,1,151,51,141,241,311,211,301,371,271,181,281,191,221,321,221,121];
plot(dist,da)

[das] = window_smooth(da,7);

%plot(dist,das);

function [data_m] = window_smooth(data,n)

L = length(data);
 

m = 0;
k = 0;
for i =1:L
    if(i<n)
        data_m(i) = data(i);
    else
       for(j = i-n+1:i)
           k = k+1;
       w1(k) = data(j);
       end
    data_m(i) = mean(w1);
    k = 0;
    end
end
end