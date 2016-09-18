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
|    1 | khash             |      0.240 |     232.520 |  625792 |           |
|    2 | ulib              |      0.270 |     232.524 |  625792 |           |
|    3 | amtl              |      0.350 |     253.144 |  625792 |           |
|    4 | mct-closed        |      0.400 |     246.016 |  625792 |           |
|    5 | hhash             |      0.430 |     293.476 |  625792 |           |
|    6 | google-dense      |      0.470 |     249.068 |  625792 |           |
|    7 | rdestl            |      0.490 |     265.432 |  625792 |           |
|    8 | ccan              |      0.650 |     224.720 |  625792 |           |
|    9 | libevent          |      0.920 |     506.676 |  625792 |           |
|   10 | stb               |      1.000 |     231.992 |  625792 |           |
|   11 | eastl             |      1.010 |     244.656 |  625792 |           |
|   12 | tommyds-fixed     |      1.020 |     788.712 |  625690 | Bug here! |
|   13 | hashit-open       |      1.080 |     346.448 |  625792 |           |
|   14 | hashit-overflow   |      1.110 |     415.944 |  636334 | Bug here! |
|   15 | gcc-libiberty     |      1.150 |     240.040 |  625792 |           |
|   16 | python            |      1.190 |     264.480 |  625792 |           |
|   17 | sys-glib          |      1.230 |     228.368 |  625792 | **        |
|   18 | hashit-chain      |      1.270 |     300.464 |  625792 |           |
|   19 | mct-linked        |      1.280 |     281.668 |  625792 |           |
|   20 | tommyds-linear    |      1.360 |     732.960 |  625690 | Bug here! |
|   21 | tommyds-dynamic   |      1.400 |     747.456 |  625792 |           |
|   22 | sys-tcl           |      1.410 |     256.964 |  625792 | **        |
|   23 | Qt-hash           |      1.440 |     246.584 |  625792 | **        |
|   24 | sys-judy          |      1.470 |     225.320 |  625792 | **        |
|   25 | uthash            |      1.470 |     617.344 |  625792 |           |
|   26 | google-sparse     |      1.530 |     225.124 |  625792 |           |
|   27 | ghthash           |      1.550 |     362.476 |  625792 |           |
|   28 | sys-apr           |      1.610 |     256.596 |  625792 | **        |
|   29 | cfu               |      1.630 |     272.360 |  625792 |           |
|   30 | generic-c-hashmap |      1.660 |     498.700 |  630572 | Bug here! |
|   31 | CDS               |      1.670 |     252.224 |  625793 | Bug here! |
|   32 | c-algoritms       |      1.710 |     268.568 |  625792 |           |
|   33 | c-hashtable       |      1.770 |     257.072 |  625792 |           |
|   34 | sys-python        |      1.870 |     675.484 |  625792 | **        |
|   35 | sys-boost         |      1.890 |     241.752 |  625792 | **        |
|   36 | stl-unordered     |      1.890 |     244.640 |  625792 | **        |
|   37 | sglib             |      2.010 |     450.568 |  625792 |           |
|   38 | htable            |      2.170 |     541.132 |  625792 |           |
|   39 | apr               |      2.200 |     253.012 |  625792 |           |
|   40 | sys-LuaHashMap    |      2.320 |     281.352 |  625792 | **        |
|   41 | ruby-st           |      2.810 |     255.492 |  625792 |           |
|   42 | st                |      2.810 |     245.772 |  625792 |           |
|   43 | google-c-dense    |      3.580 |     244.160 |  625792 |           |
|   44 | google-c-sparse   |      3.590 |     243.740 |  625792 |           |
|   45 | stl-map           |      4.920 |     245.460 |  625792 | **        |
|   46 | Qt-map            |      5.220 |     247.244 |  625792 | **        |
|   47 | sys-perl          |      5.580 |     694.992 |  625792 | **        |


** Pre-installation of Debian System Libraries is required
