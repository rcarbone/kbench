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
|    1 | khash             |      0.270 |     232.516 |  625792 |           |
|    2 | ulib              |      0.410 |     232.524 |  625792 |           |
|    3 | google-dense      |      0.440 |     249.068 |  625792 |           |
|    4 | hhash             |      0.660 |     293.476 |  625792 |           |
|    5 | ccan              |      0.910 |     227.228 |  625792 |           |
|    6 | libevent          |      1.000 |     505.752 |  625792 |           |
|    7 | python            |      1.030 |     264.480 |  625792 |           |
|    8 | hashit-open       |      1.050 |     346.448 |  625792 |           |
|    9 | stb               |      1.130 |     231.992 |  625792 |           |
|   10 | gcc-libiberty     |      1.210 |     240.040 |  625792 |           |
|   11 | hashit-overflow   |      1.210 |     415.944 |  636334 | Bug here! |
|   12 | hashit-chain      |      1.280 |     300.468 |  625792 |           |
|   13 | Qt-hash           |      1.460 |     246.824 |  625792 |           |
|   14 | sys-glib          |      1.490 |     230.148 |  625792 | **        |
|   15 | sys-tcl           |      1.610 |     256.964 |  625792 | **        |
|   16 | tommyds-fixed     |      1.610 |     788.716 |  625690 | Bug here! |
|   17 | CDS               |      1.670 |     252.224 |  625793 | Bug here! |
|   18 | sys-python        |      1.680 |     675.476 |  625792 | **        |
|   19 | tommyds-dynamic   |      1.690 |     746.400 |  625792 |           |
|   20 | generic-c-hashmap |      1.720 |     498.696 |  630572 | Bug here! |
|   21 | ghthash           |      1.760 |     362.480 |  625792 |           |
|   22 | google-sparse     |      1.780 |     225.132 |  625792 |           |
|   23 | uthash            |      1.800 |     617.740 |  625792 |           |
|   24 | tommyds-linear    |      1.820 |     732.960 |  625690 | Bug here! |
|   25 | cfu               |      1.840 |     272.360 |  625792 |           |
|   26 | c-hashtable       |      1.850 |     257.072 |  625792 |           |
|   27 | c-algoritms       |      1.860 |     268.040 |  625792 |           |
|   28 | stl-unordered     |      1.870 |     244.640 |  625792 |           |
|   29 | sys-boost         |      1.910 |     241.752 |  625792 | **        |
|   30 | sys-apr           |      1.930 |     256.596 |  625792 | **        |
|   31 | apr               |      2.060 |     253.008 |  625792 |           |
|   32 | htable            |      2.210 |     541.132 |  625792 |           |
|   33 | sglib             |      2.240 |     450.564 |  625792 |           |
|   34 | ruby-st           |      2.370 |     255.496 |  625792 |           |
|   35 | st                |      2.480 |     245.772 |  625792 |           |
|   36 | sys-LuaHashMap    |      2.680 |     281.352 |  625792 | **        |
|   37 | google-c-sparse   |      3.850 |     243.908 |  625792 |           |
|   38 | google-c-dense    |      4.280 |     244.400 |  625792 |           |
|   39 | sys-perl          |      5.220 |     694.996 |  625792 | **        |
|   40 | Qt-map            |      5.550 |     247.252 |  625792 |           |
|   41 | stl-map           |      5.940 |     245.460 |  625792 |           |


** Pre-installation of Debian System Libraries is required
