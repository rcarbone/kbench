![logo] [] kbench
=================

kbench is a test suite to benchmark several hash table implementations.

Heavily based on [Heng Li's kudb] (https://github.com/rcarbone/kudb), originally written by Heng Li in 2009 and updated by Rocco Carbone in 2016.

kbench aims to extend kudb in both the number of test cases and hash table implementations under test.

[logo]: etc/kbench.png

# Results for the impatients

Data sorted by CPU time (char * keys, unsigned values)

Linux nuc 3.2.0-4-amd64 #1 SMP Debian 3.2.81-1 x86_64 GNU/Linux

Tue Oct  4 22:03:25 CEST 2016

| Rank | Implementation    | CPU (secs) | Memory (kB) |    #    | Notes     |
| ---- | ----------------- | ---------- | ----------- | ------- | --------- |
|    1 | rdestl            |      0.780 |  289996.000 |  625792 |           |
|    2 | hashit-overflow   |      1.090 |  415916.000 |  636452 | Bug here! |
|    3 | khash             |      1.190 |  240716.000 |  625792 |           |
|    4 | ulib              |      1.190 |  240720.000 |  625792 |           |
|    5 | hashit-open       |      1.290 |  346448.000 |  625792 |           |
|    6 | libevent          |      1.320 |  506832.000 |  625792 |           |
|    7 | mct-mct           |      1.350 |  339136.000 |  625792 |           |
|    8 | amtl              |      1.370 |  332420.000 |  625792 |           |
|    9 | ccan              |      1.380 |  227108.000 |  625792 |           |
|   10 | sys-apr           |      1.450 |  256584.000 |  625792 | **        |
|   11 | sys-glib          |      1.460 |  234508.000 |  625792 | **        |
|   12 | hashit-chain      |      1.510 |  300460.000 |  625792 |           |
|   13 | google-dense      |      1.530 |  380120.000 |  625792 |           |
|   14 | gcc-libiberty     |      1.580 |  240052.000 |  625792 |           |
|   15 | ghthash           |      1.690 |  362472.000 |  625792 |           |
|   16 | c-hashtable       |      1.710 |  257360.000 |  625792 |           |
|   17 | Qt-hash           |      1.720 |  255456.000 |  625792 | **        |
|   18 | uthash            |      1.830 |  617364.000 |  625792 |           |
|   19 | python            |      1.940 |  264492.000 |  625792 |           |
|   20 | sys-tcl           |      1.940 |  256972.000 |  625792 | **        |
|   21 | redis             |      1.950 |  253212.000 |  625792 |           |
|   22 | eastl             |      1.960 |  263576.000 |  625792 |           |
|   23 | tommyds-fixed     |      1.970 |  944984.000 |  625704 | Bug here! |
|   24 | cfu               |      2.010 |  272372.000 |  625792 |           |
|   25 | c-algoritms       |      2.030 |  267252.000 |  625792 |           |
|   26 | sys-boost         |      2.070 |  263512.000 |  625792 | **        |
|   27 | generic-c-hashmap |      2.090 |  502412.000 |  698396 | Bug here! |
|   28 | apr               |      2.100 |  253016.000 |  625792 |           |
|   29 | sys-python        |      2.180 |  834320.000 |  625792 | **        |
|   30 | tommyds-dynamic   |      2.330 |  902920.000 |  625704 | Bug here! |
|   31 | CDS               |      2.390 |  252236.000 |  625792 |           |
|   32 | htable            |      2.440 |  541268.000 |  625792 |           |
|   33 | tommyds-linear    |      2.470 |  889240.000 |  625704 | Bug here! |
|   34 | stl-unordered     |      2.590 |  263588.000 |  625792 | **        |
|   35 | mct-mct           |      2.640 |  363700.000 |  625792 |           |
|   36 | sys-perl          |      2.900 |  301364.000 |  625792 | **        |
|   37 | st                |      2.950 |  245780.000 |  625792 |           |
|   38 | ruby-st           |      3.010 |  255500.000 |  625792 |           |
|   39 | sys-judy          |      3.150 |  259364.000 |  625792 | **        |
|   40 | sglib             |      3.320 |  450572.000 |  625792 |           |
|   41 | stb               |      3.450 |  282112.000 |  625792 |           |
|   42 | google-sparse     |      4.410 |  251364.000 |  625792 |           |
|   43 | sys-LuaHashMap    |      7.150 |  354948.000 |  625792 | **        |
|   44 | google-c-dense    |      7.350 |  244404.000 |  625792 |           |
|   45 | google-c-sparse   |      7.420 |  244404.000 |  625792 |           |
|   46 | stl-map           |      8.000 |  264988.000 |  625792 | **        |
|   47 | Qt-map            |      8.880 |  266776.000 |  625792 | **        |
|   48 | lua-table         |    107.730 |  264740.000 |  625792 |           |


** Pre-installation of Debian System Libraries is required
