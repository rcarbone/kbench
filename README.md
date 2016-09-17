![logo] [] kbench
=================

kbench is a test suite to benchmark several hash table implementations.

Heavily based on [Heng Li's kudb] (https://github.com/rcarbone/kudb), originally written by Heng Li in 2009 and updated by Rocco Carbone in 2016.

kbench aims to extend kudb in both the number of test cases and hash table implementations under test.

[logo]: etc/kbench.png

# Results for the impatients

Data sorted by CPU time (unsigned keys, unsigned values)

Linux nuc 3.2.0-4-amd64 #1 SMP Debian 3.2.81-1 x86_64 GNU/Linux

Wed Sep 14 22:18:52 CEST 2016

| Rank | Implementation    | CPU (secs) | Memory (MB) |    #    | Notes     |
| ---- | ----------------- | ---------- | ----------- | ------- | --------- |
|    1 | ulib              |      0.300 |     232.524 |  625792 |           |
|    2 | amtl              |      0.380 |     253.148 |  625792 |           |
|    3 | khash             |      0.400 |     232.516 |  625792 |           |
|    4 | google-dense      |      0.460 |     249.068 |  625792 |           |
|    5 | rdestl            |      0.520 |     265.168 |  625792 |           |
|    6 | hhash             |      0.590 |     293.476 |  625792 |           |
|    7 | mct-closed        |      0.610 |     248.924 |  625792 |           |
|    8 | ccan              |      0.760 |     225.512 |  625792 |           |
|    9 | hashit-open       |      1.010 |     346.448 |  625792 |           |
|   10 | tommyds-fixed     |      1.060 |     788.716 |  625690 | Bug here! |
|   11 | libevent          |      1.100 |     507.468 |  625792 |           |
|   12 | stb               |      1.170 |     231.992 |  625792 |           |
|   13 | gcc-libiberty     |      1.220 |     240.040 |  625792 |           |
|   14 | eastl             |      1.270 |     244.656 |  625792 |           |
|   15 | uthash            |      1.300 |     616.948 |  625792 |           |
|   16 | sys-glib          |      1.310 |     228.760 |  625792 | **        |
|   17 | python            |      1.330 |     264.480 |  625792 |           |
|   18 | mct-linked        |      1.340 |     281.668 |  625792 |           |
|   19 | hashit-overflow   |      1.350 |     415.940 |  636334 | Bug here! |
|   20 | tommyds-dynamic   |      1.350 |     746.664 |  625792 |           |
|   21 | Qt-hash           |      1.540 |     246.580 |  625792 |           |
|   22 | ghthash           |      1.590 |     362.480 |  625792 |           |
|   23 | hashit-chain      |      1.600 |     300.468 |  625792 |           |
|   24 | tommyds-linear    |      1.610 |     732.960 |  625690 | Bug here! |
|   25 | sys-tcl           |      1.620 |     256.964 |  625792 | **        |
|   26 | c-hashtable       |      1.630 |     257.072 |  625792 |           |
|   27 | CDS               |      1.640 |     252.224 |  625793 | Bug here! |
|   28 | c-algoritms       |      1.660 |     267.380 |  625792 |           |
|   29 | stl-unordered     |      1.790 |     244.640 |  625792 |           |
|   30 | sys-apr           |      1.890 |     256.596 |  625792 | **        |
|   31 | google-sparse     |      1.890 |     225.124 |  625792 |           |
|   32 | sys-python        |      1.900 |     675.484 |  625792 | **        |
|   33 | cfu               |      1.940 |     272.360 |  625792 |           |
|   34 | apr               |      2.050 |     253.004 |  625792 |           |
|   35 | generic-c-hashmap |      2.120 |     498.700 |  630572 | Bug here! |
|   36 | sys-boost         |      2.270 |     241.752 |  625792 | **        |
|   37 | htable            |      2.450 |     541.132 |  625792 |           |
|   38 | sglib             |      2.660 |     450.568 |  625792 |           |
|   39 | st                |      2.810 |     245.772 |  625792 |           |
|   40 | ruby-st           |      2.920 |     255.492 |  625792 |           |
|   41 | sys-LuaHashMap    |      3.790 |     281.344 |  625792 | **        |
|   42 | google-c-dense    |      4.900 |     244.400 |  625792 |           |
|   43 | google-c-sparse   |      5.090 |     244.400 |  625792 |           |
|   44 | stl-map           |      6.370 |     245.460 |  625792 |           |
|   45 | Qt-map            |      6.640 |     247.244 |  625792 |           |
|   46 | sys-perl          |      6.860 |     694.992 |  625792 | **        |


** Pre-installation of Debian System Libraries is required
