![logo] [] kbench
=================

kbench is a test suite to benchmark several hash table implementations.

Heavily based on [Heng Li's kudb] (https://github.com/rcarbone/kudb), originally written by Heng Li in 2009 and updated by Rocco Carbone in 2016.

kbench aims to extend kudb in both the number of test cases and hash table implementations under test.

[logo]: etc/kbench.png

# Results for the impatients

Data sorted by CPU time (char * keys, unsigned values)

Linux nuc 3.2.0-4-amd64 #1 SMP Debian 3.2.81-1 x86_64 GNU/Linux

Tue Oct 25 13:25:20 CEST 2016

| Rank | Implementation    | CPU (secs) | Memory (Mb) |    #    | Notes     |
| ---- | ----------------- | ---------- | ----------- | ------- | --------- |
|    1 | rigtorp-hashmap   |      0.760 |     347.100 |  625792 |           |
|    2 | rdestl            |      0.850 |     290.004 |  625792 |           |
|    3 | ulib              |      1.010 |     240.724 |  625792 |           |
|    4 | libevent          |      1.110 |     504.988 |  625792 |           |
|    5 | khash             |      1.140 |     240.716 |  625792 |           |
|    6 | ccan              |      1.210 |     227.240 |  625792 |           |
|    7 | hashit-overflow   |      1.290 |     415.924 |  636452 | Bug here! |
|    8 | hashit-open       |      1.300 |     346.448 |  625792 |           |
|    9 | mct-closed        |      1.380 |     339.140 |  625792 |           |
|   10 | amtl              |      1.410 |     332.428 |  625792 |           |
|   11 | sys-apr           |      1.410 |     256.584 |  625792 | **        |
|   12 | sys-glib          |      1.440 |     228.968 |  625792 | **        |
|   13 | oddou-hashmap     |      1.460 |     299.112 |  625792 |           |
|   14 | google-dense      |      1.470 |     380.128 |  625792 | **        |
|   15 | gcc-libiberty     |      1.500 |     240.180 |  625792 |           |
|   16 | uthash            |      1.540 |     618.028 |  625792 |           |
|   17 | tommyds-fixed     |      1.570 |     944.988 |  625792 |           |
|   18 | python            |      1.610 |     264.492 |  625792 |           |
|   19 | Qt-hash           |      1.700 |     255.456 |  625792 | **        |
|   20 | cfu               |      1.710 |     272.376 |  625792 |           |
|   21 | ghthash           |      1.720 |     362.476 |  625792 |           |
|   22 | tommyds-dynamic   |      1.760 |     903.452 |  625792 |           |
|   23 | generic-c-hashmap |      1.770 |     502.416 |  698396 | Bug here! |
|   24 | hashit-chain      |      1.830 |     300.464 |  625792 |           |
|   25 | CDS               |      1.870 |     252.236 |  625792 |           |
|   26 | tommyds-linear    |      1.900 |     889.244 |  625792 |           |
|   27 | eastl             |      1.910 |     263.584 |  625792 |           |
|   28 | c-hashtable       |      1.940 |     257.360 |  625792 |           |
|   29 | sys-tcl           |      1.960 |     256.976 |  625792 | **        |
|   30 | apr               |      1.970 |     253.012 |  625792 |           |
|   31 | c-algoritms       |      2.000 |     266.996 |  625792 |           |
|   32 | sys-boost         |      2.080 |     263.516 |  625792 | **        |
|   33 | sys-python        |      2.160 |     834.312 |  625792 | **        |
|   34 | redis             |      2.280 |     253.212 |  625792 |           |
|   35 | htable            |      2.380 |     541.268 |  625792 |           |
|   36 | gcc-unordered_map |      2.550 |     263.592 |  625792 | **        |
|   37 | ruby-st           |      2.950 |     255.504 |  625792 |           |
|   38 | sys-judy          |      3.040 |     259.372 |  625792 | **        |
|   39 | mct-linked        |      3.110 |     363.708 |  625792 |           |
|   40 | sglib             |      3.220 |     450.572 |  625792 |           |
|   41 | sys-perl          |      3.300 |     301.240 |  625792 | **        |
|   42 | stb               |      3.390 |     282.116 |  625792 |           |
|   43 | st                |      3.530 |     245.784 |  625792 |           |
|   44 | google-sparse     |      4.430 |     251.376 |  625792 | **        |
|   45 | sys-LuaHashMap    |      6.110 |     354.948 |  625792 | **        |
|   46 | google-c-sparse   |      6.140 |     244.408 |  625792 |           |
|   47 | google-c-dense    |      6.480 |     244.408 |  625792 |           |
|   48 | gcc-map           |      7.730 |     264.996 |  625792 | **        |
|   49 | Qt-map            |      8.560 |     266.776 |  625792 | **        |
|   50 | lua-table         |    102.350 |     264.744 |  625792 |           |


** Pre-installation of Debian System Libraries is required
