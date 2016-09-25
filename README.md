![logo] [] kbench
=================

kbench is a test suite to benchmark several hash table implementations.

Heavily based on [Heng Li's kudb] (https://github.com/rcarbone/kudb), originally written by Heng Li in 2009 and updated by Rocco Carbone in 2016.

kbench aims to extend kudb in both the number of test cases and hash table implementations under test.

[logo]: etc/kbench.png

# Results for the impatients

Data sorted by CPU time (unsigned keys, unsigned values)

Linux nuc 3.2.0-4-amd64 #1 SMP Debian 3.2.81-1 x86_64 GNU/Linux

Sun Sep 25 22:32:38 CEST 2016

| Rank | Implementation    | CPU (secs) | Memory (MB) |    #    | Notes     |
| ---- | ----------------- | ---------- | ----------- | ------- | --------- |
|    1 | ulib              |      0.280 |     232.528 |  625792 |           |
|    2 | khash             |      0.300 |     232.520 |  625792 |           |
|    3 | amtl              |      0.360 |     253.148 |  625792 |           |
|    4 | mct-mct           |      0.440 |     248.924 |  625792 |           |
|    5 | rdestl            |      0.540 |     265.432 |  625792 |           |
|    6 | google-dense      |      0.590 |     249.072 |  625792 |           |
|    7 | ccan              |      0.660 |     227.100 |  625792 |           |
|    8 | hhash             |      0.820 |     293.476 |  625792 |           |
|    9 | libevent          |      0.820 |     506.416 |  625792 |           |
|   10 | gcc-libiberty     |      1.020 |     240.040 |  625792 |           |
|   11 | hashit-open       |      1.050 |     346.448 |  625792 |           |
|   12 | mct-mct           |      1.070 |     281.672 |  625792 |           |
|   13 | stb               |      1.220 |     231.992 |  625792 |           |
|   14 | Qt-hash           |      1.240 |     246.580 |  625792 |           |
|   15 | uthash            |      1.260 |     618.008 |  625792 |           |
|   16 | tommyds-dynamic   |      1.290 |     746.404 |  625792 |           |
|   17 | python            |      1.350 |     264.480 |  625792 |           |
|   18 | hashit-overflow   |      1.360 |     415.944 |  636334 | Bug here! |
|   19 | sys-glib          |      1.360 |     230.420 |  625792 | **        |
|   20 | c-algoritms       |      1.400 |     268.176 |  625792 |           |
|   21 | tommyds-fixed     |      1.400 |     788.716 |  625690 | Bug here! |
|   22 | eastl             |      1.440 |     244.660 |  625792 |           |
|   23 | tommyds-linear    |      1.440 |     732.960 |  625690 | Bug here! |
|   24 | hashit-chain      |      1.480 |     300.468 |  625792 |           |
|   25 | sys-judy          |      1.490 |     225.320 |  625792 | **        |
|   26 | CDS               |      1.640 |     252.232 |  625793 | Bug here! |
|   27 | sys-tcl           |      1.660 |     256.964 |  625792 | **        |
|   28 | sys-python        |      1.750 |     675.488 |  625792 | **        |
|   29 | apr               |      1.850 |     253.012 |  625792 |           |
|   30 | cfu               |      1.870 |     272.360 |  625792 |           |
|   31 | sys-boost         |      1.930 |     241.752 |  625792 | **        |
|   32 | ghthash           |      1.950 |     362.480 |  625792 |           |
|   33 | sys-apr           |      1.960 |     256.596 |  625792 | **        |
|   34 | generic-c-hashmap |      1.990 |     498.700 |  630572 | Bug here! |
|   35 | stl-unordered     |      1.990 |     244.640 |  625792 | **        |
|   36 | c-hashtable       |      2.030 |     257.480 |  625792 |           |
|   37 | google-sparse     |      2.220 |     225.136 |  625792 |           |
|   38 | sglib             |      2.380 |     450.568 |  625792 |           |
|   39 | htable            |      2.410 |     541.132 |  625792 |           |
|   40 | sys-LuaHashMap    |      2.620 |     281.360 |  625792 | **        |
|   41 | ruby-st           |      2.690 |     255.492 |  625792 |           |
|   42 | st                |      2.730 |     245.776 |  625792 |           |
|   43 | google-c-dense    |      3.810 |     244.404 |  625792 |           |
|   44 | google-c-sparse   |      4.060 |     244.404 |  625792 |           |
|   45 | stl-map           |      6.920 |     245.460 |  625792 | **        |
|   46 | Qt-map            |      7.190 |     247.236 |  625792 | **        |
|   47 | sys-perl          |      7.640 |     694.984 |  625792 | **        |


** Pre-installation of Debian System Libraries is required
