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
|    1 | rdestl            |      0.950 |     290.000 |  625792 |           |
|    2 | rigtorp-hashmap   |      1.060 |     347.096 |  625792 |           |
|    3 | khash             |      1.070 |     240.720 |  625792 |           |
|    4 | ulib              |      1.090 |     240.724 |  625792 |           |
|    5 | hashit-open       |      1.200 |     346.452 |  625792 |           |
|    6 | hashit-overflow   |      1.270 |     415.924 |  636452 | Bug here! |
|    7 | ccan              |      1.310 |     227.108 |  625792 |           |
|    8 | libevent          |      1.320 |     506.704 |  625792 |           |
|    9 | amtl              |      1.370 |     332.424 |  625792 |           |
|   10 | mct-closed        |      1.380 |     339.140 |  625792 |           |
|   11 | sys-glib          |      1.430 |     228.376 |  625792 | **        |
|   12 | gcc-libiberty     |      1.590 |     240.052 |  625792 |           |
|   13 | google-dense      |      1.590 |     380.124 |  625792 |           |
|   14 | oddou-hashmap     |      1.620 |     299.112 |  625792 |           |
|   15 | uthash            |      1.620 |     617.632 |  625792 |           |
|   16 | hashit-chain      |      1.680 |     300.464 |  625792 |           |
|   17 | ghthash           |      1.750 |     362.476 |  625792 |           |
|   18 | Qt-hash           |      1.750 |     255.452 |  625792 | **        |
|   19 | c-hashtable       |      1.810 |     257.492 |  625792 |           |
|   20 | eastl             |      1.840 |     263.580 |  625792 |           |
|   21 | sys-apr           |      1.850 |     256.584 |  625792 | **        |
|   22 | cfu               |      1.870 |     272.376 |  625792 |           |
|   23 | generic-c-hashmap |      1.880 |     502.416 |  698396 | Bug here! |
|   24 | apr               |      1.900 |     253.016 |  625792 |           |
|   25 | c-algoritms       |      1.940 |     267.788 |  625792 |           |
|   26 | sys-tcl           |      1.960 |     256.976 |  625792 | **        |
|   27 | python            |      2.020 |     264.496 |  625792 |           |
|   28 | CDS               |      2.120 |     252.240 |  625792 |           |
|   29 | sys-boost         |      2.310 |     263.512 |  625792 | **        |
|   30 | sys-python        |      2.330 |     834.328 |  625792 | **        |
|   31 | tommyds-dynamic   |      2.350 |     903.984 |  625704 | Bug here! |
|   32 | stl-unordered     |      2.430 |     263.592 |  625792 |           |
|   33 | tommyds-fixed     |      2.480 |     944.988 |  625704 | Bug here! |
|   34 | tommyds-linear    |      2.580 |     889.244 |  625704 | Bug here! |
|   35 | redis             |      2.770 |     253.216 |  625792 |           |
|   36 | htable            |      2.930 |     541.268 |  625792 |           |
|   37 | mct-linked        |      3.150 |     363.704 |  625792 |           |
|   38 | sys-judy          |      3.160 |     259.448 |  625792 | **        |
|   39 | sys-perl          |      3.450 |     301.368 |  625792 | **        |
|   40 | sglib             |      3.480 |     450.576 |  625792 |           |
|   41 | st                |      3.660 |     245.784 |  625792 |           |
|   42 | stb               |      3.700 |     282.116 |  625792 |           |
|   43 | ruby-st           |      3.730 |     255.504 |  625792 |           |
|   44 | google-sparse     |      4.660 |     251.372 |  625792 |           |
|   45 | sys-LuaHashMap    |      6.150 |     354.952 |  625792 | **        |
|   46 | google-c-sparse   |      6.960 |     244.408 |  625792 |           |
|   47 | google-c-dense    |      7.030 |     244.408 |  625792 |           |
|   48 | stl-map           |      9.200 |     264.992 |  625792 |           |
|   49 | Qt-map            |      9.480 |     266.776 |  625792 | **        |
|   50 | lua-table         |    121.600 |     264.744 |  625792 |           |


** Pre-installation of Debian System Libraries is required
