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
|    1 | khash             |      0.310 |     232,516 |  625792 |           |
|    2 | ulib              |      0.380 |     232,524 |  625792 |           |
|    3 | hhash             |      0.440 |     293,476 |  625792 |           |
|    4 | google-dense      |      0.480 |     249,068 |  625792 | **        |
|    5 | ccan              |      0.520 |     227,364 |  625792 |           |
|    6 | hashit-overflow   |      0.880 |     415,944 |  636334 | Bug here! |
|    7 | hashit-open       |      1.070 |     346,448 |  625792 |           |
|    8 | libevent          |      1.150 |     507,204 |  625792 |           |
|    9 | gcc-libiberty     |      1.160 |     240,040 |  625792 |           |
|   10 | stb               |      1.180 |     231,992 |  625792 |           |
|   11 | python            |      1.210 |     264,480 |  625792 |           |
|   12 | tommyds-dynamic   |      1.240 |     747,720 |  625792 |           |
|   13 | sys-glib          |      1.320 |     230,544 |  625792 | **        |
|   14 | tommyds-fixed     |      1.420 |     788,716 |  625690 | Bug here! |
|   15 | c-algoritms       |      1.480 |     267,908 |  625792 |           |
|   16 | tommyds-linear    |      1.500 |     732,960 |  625690 | Bug here! |
|   17 | uthash            |      1.530 |     618,136 |  625792 |           |
|   18 | hashit-chain      |      1.580 |     300,464 |  625792 |           |
|   19 | google-sparse     |      1.590 |     225,132 |  625792 | **        |
|   20 | CDS               |      1.650 |     252,224 |  625793 | Bug here! |
|   21 | sys-tcl           |      1.690 |     256,964 |  625792 | **        |
|   22 | ghthash           |      1.720 |     362,476 |  625792 |           |
|   23 | sys-apr           |      1.720 |     256,596 |  625792 | **        |
|   24 | sys-unordered-map |      1.850 |     244,640 |  625792 | **        |
|   25 | apr               |      1.860 |     253,012 |  625792 |           |
|   26 | generic-c-hashmap |      2.010 |     498,696 |  630572 | Bug here! |
|   27 | c-hashtable       |      2.030 |     257,608 |  625792 |           |
|   28 | cfu               |      2.160 |     272,360 |  625792 |           |
|   29 | sys-python        |      2.180 |     675,476 |  625792 | **        |
|   30 | sys-LuaHashMap    |      2.400 |     281,352 |  625792 | **        |
|   31 | sglib             |      2.420 |     450,564 |  625792 |           |
|   32 | htable            |      2.610 |     541,132 |  625792 |           |
|   33 | st                |      2.630 |     245,776 |  625792 |           |
|   34 | ruby-st           |      2.860 |     255,496 |  625792 |           |
|   35 | google-c-sparse   |      3.600 |     244,404 |  625792 |           |
|   36 | google-c-dense    |      4.330 |     244,400 |  625792 |           |
|   37 | sys-perl          |      5.700 |     694,992 |  625792 | **        |


** Pre-installation of Debian System Libraries is required
