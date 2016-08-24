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

| Rank | Implementation    | CPU (secs) | Memory (kB) |    #    | Notes     |
| ---- | ----------------- | ---------- | ----------- | ------- | --------- |
|    1 | khash             |      0.240 |  232520.000 |  625792 |           |
|    2 | ulib              |      0.270 |  232528.000 |  625792 |           |
|    3 | hhash             |      0.420 |  293472.000 |  625792 |           |
|    4 | ccan              |      0.550 |  225388.000 |  625792 |           |
|    5 | hashit-overflow   |      0.900 |  415940.000 |  636334 | Bug here! |
|    6 | gcc-libiberty     |      1.000 |  240176.000 |  625792 |           |
|    7 | hashit-open       |      1.080 |  346444.000 |  625792 |           |
|    8 | libevent          |      1.080 |  505492.000 |  625792 |           |
|    9 | stb               |      1.080 |  231996.000 |  625792 |           |
|   10 | python            |      1.170 |  264484.000 |  625792 |           |
|   11 | uthash            |      1.200 |  617084.000 |  625792 |           |
|   12 | hashit-chain      |      1.230 |  300464.000 |  625792 |           |
|   13 | sys-glib          |      1.260 |  233708.000 |  625792 |           |
|   14 | ghthash           |      1.310 |  362476.000 |  625792 |           |
|   15 | CDS               |      1.390 |  252228.000 |  625793 | Bug here! |
|   16 | sys-tcl           |      1.420 |  256968.000 |  625792 |           |
|   17 | c-hashtable       |      1.440 |  257076.000 |  625792 |           |
|   18 | generic-c-hashmap |      1.610 |  498700.000 |  630572 | Bug here! |
|   19 | c-algoritms       |      1.650 |  267912.000 |  625792 |           |
|   20 | cfu               |      1.790 |  272364.000 |  625792 |           |
|   21 | sys-apr           |      1.910 |  256592.000 |  625792 |           |
|   22 | sys-python        |      1.910 |  675476.000 |  625792 |           |
|   23 | apr               |      2.190 |  253016.000 |  625792 |           |
|   24 | ruby-st           |      2.240 |  255496.000 |  625792 |           |
|   25 | st                |      2.260 |  245776.000 |  625792 |           |
|   26 | sys-LuaHashMap    |      2.270 |  281348.000 |  625792 |           |
|   27 | htable            |      2.610 |  541136.000 |  625792 |           |
|   28 | sglib             |      2.610 |  450564.000 |  625792 |           |
|   29 | google-c-sparse   |      3.500 |  243744.000 |  625792 |           |
|   30 | google-c-dense    |      3.560 |  243912.000 |  625792 |           |
|   31 | sys-perl          |      5.430 |  695124.000 |  625792 |           |


* Pre-installation of Debian System Libraries is required
