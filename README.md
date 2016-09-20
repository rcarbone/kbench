![logo] [] kbench
=================

kbench is a test suite to benchmark several hash table implementations.

Heavily based on [Heng Li's kudb] (https://github.com/rcarbone/kudb), originally written by Heng Li in 2009 and updated by Rocco Carbone in 2016.

kbench aims to extend kudb in both the number of test cases and hash table implementations under test.

[logo]: etc/kbench.png

# Results for the impatients

Data sorted by CPU time (unsigned keys, unsigned values)

Linux nuc 3.2.0-4-amd64 #1 SMP Debian 3.2.81-1 x86_64 GNU/Linux

Tue Sep 20 19:56:28 CEST 2016

| Rank | Implementation    | CPU (secs) | Memory (MB) |    #    | Notes     |
| ---- | ----------------- | ---------- | ----------- | ------- | --------- |
|    1 | ulib              |      0.250 |     232.524 |  625792 |           |
|    2 | khash             |      0.260 |     232.520 |  625792 |           |
|    3 | amtl              |      0.350 |     253.148 |  625792 |           |
|    4 | google-dense      |      0.400 |     249.068 |  625792 |           |
|    5 | hhash             |      0.420 |     293.472 |  625792 |           |
|    6 | mct-closed        |      0.500 |     248.924 |  625792 |           |
|    7 | rdestl            |      0.630 |     265.432 |  625792 |           |
|    8 | ccan              |      0.780 |     223.804 |  625792 |           |
|    9 | hashit-overflow   |      0.910 |     415.944 |  636334 | Bug here! |
|   10 | libevent          |      1.000 |     507.072 |  625792 |           |
|   11 | hashit-open       |      1.040 |     346.448 |  625792 |           |
|   12 | mct-linked        |      1.060 |     281.668 |  625792 |           |
|   13 | stb               |      1.080 |     231.992 |  625792 |           |
|   14 | tommyds-fixed     |      1.090 |     788.716 |  625690 | Bug here! |
|   15 | eastl             |      1.120 |     244.656 |  625792 |           |
|   16 | gcc-libiberty     |      1.210 |     240.040 |  625792 |           |
|   17 | Qt-hash           |      1.230 |     246.580 |  625792 |           |
|   18 | tommyds-dynamic   |      1.260 |     746.396 |  625792 |           |
|   19 | python            |      1.270 |     264.480 |  625792 |           |
|   20 | sys-glib          |      1.270 |     234.304 |  625792 | **        |
|   21 | tommyds-linear    |      1.340 |     732.960 |  625690 | Bug here! |
|   22 | ghthash           |      1.450 |     362.480 |  625792 |           |
|   23 | sys-judy          |      1.480 |     225.324 |  625792 | **        |
|   24 | c-algoritms       |      1.520 |     266.984 |  625792 |           |
|   25 | uthash            |      1.520 |     617.344 |  625792 |           |
|   26 | google-sparse     |      1.530 |     225.124 |  625792 |           |
|   27 | sys-apr           |      1.610 |     256.596 |  625792 | **        |
|   28 | sys-tcl           |      1.660 |     256.964 |  625792 | **        |
|   29 | CDS               |      1.700 |     252.224 |  625793 | Bug here! |
|   30 | hashit-chain      |      1.710 |     300.468 |  625792 |           |
|   31 | c-hashtable       |      1.770 |     257.872 |  625792 |           |
|   32 | stl-unordered     |      1.800 |     244.640 |  625792 | **        |
|   33 | cfu               |      1.850 |     272.360 |  625792 |           |
|   34 | sys-python        |      1.850 |     675.484 |  625792 | **        |
|   35 | sys-boost         |      1.900 |     241.752 |  625792 | **        |
|   36 | generic-c-hashmap |      1.910 |     498.700 |  630572 | Bug here! |
|   37 | apr               |      2.250 |     253.012 |  625792 |           |
|   38 | sys-LuaHashMap    |      2.280 |     281.352 |  625792 | **        |
|   39 | st                |      2.310 |     245.772 |  625792 |           |
|   40 | htable            |      2.500 |     541.132 |  625792 |           |
|   41 | sglib             |      2.580 |     450.568 |  625792 |           |
|   42 | judy-template     |      2.740 |     238.860 |  625792 |           |
|   43 | ruby-st           |      2.920 |     255.492 |  625792 |           |
|   44 | judyarray         |      2.950 |     457.344 | 4999980 | Bug here! |
|   45 | google-c-sparse   |      3.770 |     243.740 |  625792 |           |
|   46 | google-c-dense    |      3.990 |     244.400 |  625792 |           |
|   47 | sys-perl          |      5.050 |     694.980 |  625792 | **        |
|   48 | stl-map           |      5.700 |     245.460 |  625792 | **        |
|   49 | Qt-map            |      5.910 |     247.244 |  625792 | **        |


** Pre-installation of Debian System Libraries is required
