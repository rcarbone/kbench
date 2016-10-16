![logo] [] kbench
=================

kbench is a test suite to benchmark several hash table implementations.

Heavily based on [Heng Li's kudb] (https://github.com/rcarbone/kudb), originally written by Heng Li in 2009 and updated by Rocco Carbone in 2016.

kbench aims to extend kudb in both the number of test cases and hash table implementations under test.

[logo]: etc/kbench.png

# Results for the impatients

Data sorted by CPU time (char * keys, unsigned values)

Linux nuc 3.2.0-4-amd64 #1 SMP Debian 3.2.81-1 x86_64 GNU/Linux

Sun Oct 16 14:15:46 CEST 2016

| Rank | Implementation    | CPU (secs) | Memory (kB) |    #    | Notes     |
| ---- | ----------------- | ---------- | ----------- | ------- | --------- |
|    1 | rigtorp-hashmap   |      0.850 |     347.096 |  625792 |           |
|    2 | rdestl            |      0.870 |     290.000 |  625792 |           |
|    3 | ulib              |      1.140 |     240.724 |  625792 |           |
|    4 | khash             |      1.170 |     240.720 |  625792 |           |
|    5 | ccan              |      1.200 |     227.108 |  625792 |           |
|    6 | amtl              |      1.250 |     332.432 |  625792 |           |
|    7 | libevent          |      1.390 |     507.232 |  625792 |           |
|    8 | mct-closed        |      1.390 |     339.140 |  625792 |           |
|    9 | hashit-overflow   |      1.400 |     415.924 |  636452 | Bug here! |
|   10 | sys-apr           |      1.450 |     256.588 |  625792 | **        |
|   11 | sys-glib          |      1.480 |     228.376 |  625792 | **        |
|   12 | google-dense      |      1.490 |     380.124 |  625792 |           |
|   13 | gcc-libiberty     |      1.530 |     240.188 |  625792 |           |
|   14 | python            |      1.640 |     264.496 |  625792 |           |
|   15 | c-algoritms       |      1.680 |     266.864 |  625792 |           |
|   16 | uthash            |      1.680 |     618.424 |  625792 |           |
|   17 | c-hashtable       |      1.710 |     257.088 |  625792 |           |
|   18 | cfu               |      1.740 |     272.376 |  625792 |           |
|   19 | hashit-open       |      1.740 |     346.452 |  625792 |           |
|   20 | generic-c-hashmap |      1.840 |     502.416 |  698396 | Bug here! |
|   21 | sys-tcl           |      1.870 |     256.976 |  625792 | **        |
|   22 | redis             |      1.900 |     253.216 |  625792 |           |
|   23 | hashit-chain      |      1.950 |     300.464 |  625792 |           |
|   24 | eastl             |      1.960 |     263.580 |  625792 |           |
|   25 | apr               |      1.980 |     253.016 |  625792 |           |
|   26 | Qt-hash           |      2.010 |     255.452 |  625792 | **        |
|   27 | sys-boost         |      2.040 |     263.512 |  625792 | **        |
|   28 | tommyds-fixed     |      2.060 |     944.988 |  625704 | Bug here! |
|   29 | ghthash           |      2.110 |     362.476 |  625792 |           |
|   30 | tommyds-dynamic   |      2.120 |     903.980 |  625704 | Bug here! |
|   31 | CDS               |      2.260 |     252.240 |  625792 |           |
|   32 | stl-unordered     |      2.300 |     263.592 |  625792 |           |
|   33 | sys-python        |      2.490 |     834.324 |  625792 | **        |
|   34 | tommyds-linear    |      2.500 |     889.244 |  625704 | Bug here! |
|   35 | mct-linked        |      2.630 |     363.704 |  625792 |           |
|   36 | ruby-st           |      2.950 |     255.504 |  625792 |           |
|   37 | htable            |      3.020 |     541.268 |  625792 |           |
|   38 | sglib             |      3.300 |     450.576 |  625792 |           |
|   39 | sys-judy          |      3.310 |     259.368 |  625792 | **        |
|   40 | sys-perl          |      3.380 |     301.368 |  625792 | **        |
|   41 | st                |      3.630 |     245.784 |  625792 |           |
|   42 | stb               |      3.990 |     282.116 |  625792 |           |
|   43 | google-sparse     |      4.680 |     251.372 |  625792 |           |
|   44 | sys-LuaHashMap    |      6.160 |     354.948 |  625792 | **        |
|   45 | google-c-dense    |      7.430 |     244.408 |  625792 |           |
|   46 | google-c-sparse   |      7.600 |     244.408 |  625792 |           |
|   47 | stl-map           |      8.360 |     264.992 |  625792 |           |
|   48 | Qt-map            |      8.750 |     266.764 |  625792 | **        |
|   49 | lua-table         |    120.550 |     264.744 |  625792 |           |


** Pre-installation of Debian System Libraries is required
