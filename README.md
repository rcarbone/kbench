![logo] [] kbench
=================

kbench is a test suite to benchmark several hash table implementations.

Heavily based on [Heng Li's kudb] (https://github.com/rcarbone/kudb), originally written by Heng Li in 2009 and updated by Rocco Carbone in 2016.

kbench aims to extend kudb in both the number of test cases and hash table implementations under test.

[logo]: etc/kbench.png

# Results for the impatients

Data sorted by CPU time (unsigned keys, unsigned values)

Wed Aug 24 15:51:59 CEST 2016

Linux nuc 3.2.0-4-amd64 #1 SMP Debian 3.2.81-1 x86_64 GNU/Linux

| Rank | Implementation    | CPU (secs) | Memory (MB) |    #    | Notes     |
| ---- | ----------------- | ---------- | ----------- | ------- | --------- |
|    1 | khash             |      0.320 |     232,516 |  625792 |           |
|    2 | ulib              |      0.330 |     232,524 |  625792 |           |
|    3 | hhash             |      0.450 |     293,472 |  625792 |           |
|    4 | google-dense      |      0.600 |     249,068 |  625792 |           |
|    5 | ccan              |      0.690 |     227,492 |  625792 |           |
|    6 | rdestl            |      0.710 |     265,432 |  625792 |           |
|    7 | libevent          |      0.790 |     506,016 |  625792 |           |
|    8 | hashit-overflow   |      0.960 |     415,944 |  636334 | Bug here! |
|    9 | tommyds-fixed     |      1.070 |     788,716 |  625690 | Bug here! |
|   10 | eastl             |      1.170 |     244,656 |  625792 |           |
|   11 | python            |      1.180 |     264,480 |  625792 |           |
|   12 | hashit-open       |      1.190 |     346,444 |  625792 |           |
|   13 | stb               |      1.200 |     231,992 |  625792 |           |
|   14 | gcc-libiberty     |      1.250 |     240,040 |  625792 |           |
|   15 | uthash            |      1.260 |     618,400 |  625792 |           |
|   16 | tommyds-dynamic   |      1.320 |     747,456 |  625792 |           |
|   17 | sys-glib          |      1.420 |     234,104 |  625792 | **        |
|   18 | tommyds-linear    |      1.420 |     732,960 |  625690 | Bug here! |
|   19 | ghthash           |      1.460 |     362,480 |  625792 |           |
|   20 | hashit-chain      |      1.560 |     300,468 |  625792 |           |
|   21 | Qt-hash           |      1.570 |     246,820 |  625792 |           |
|   22 | CDS               |      1.610 |     252,224 |  625793 | Bug here! |
|   23 | c-algoritms       |      1.640 |     268,436 |  625792 |           |
|   24 | c-hashtable       |      1.640 |     257,740 |  625792 |           |
|   25 | sys-tcl           |      1.640 |     256,964 |  625792 | **        |
|   26 | stl-unordered     |      1.830 |     244,636 |  625792 |           |
|   27 | sys-apr           |      1.890 |     256,596 |  625792 | **        |
|   28 | cfu               |      1.900 |     272,360 |  625792 |           |
|   29 | generic-c-hashmap |      2.010 |     498,700 |  630572 | Bug here! |
|   30 | apr               |      2.180 |     253,008 |  625792 |           |
|   31 | sys-python        |      2.290 |     675,484 |  625792 | **        |
|   32 | htable            |      2.320 |     541,132 |  625792 |           |
|   33 | sys-LuaHashMap    |      2.370 |     281,340 |  625792 | **        |
|   34 | sys-boost         |      2.380 |     241,752 |  625792 | **        |
|   35 | google-sparse     |      2.620 |     225,124 |  625792 |           |
|   36 | st                |      2.800 |     245,772 |  625792 |           |
|   37 | sglib             |      2.870 |     450,568 |  625792 |           |
|   38 | ruby-st           |      2.980 |     255,492 |  625792 |           |
|   39 | google-c-dense    |      3.570 |     244,400 |  625792 |           |
|   40 | google-c-sparse   |      3.970 |     243,740 |  625792 |           |
|   41 | stl-map           |      6.250 |     245,460 |  625792 |           |
|   42 | sys-perl          |      6.670 |     694,992 |  625792 | **        |
|   43 | Qt-map            |      6.670 |     247,248 |  625792 |           |


** Pre-installation of Debian System Libraries is required
