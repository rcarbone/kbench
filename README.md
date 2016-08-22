![logo] [] kbench
=================

kbench is a test suite to benchmark several hash table implementations.

Heavily based on [Heng Li's kudb] (https://github.com/rcarbone/kudb), originally written by Heng Li in 2009 and updated by Rocco Carbone in 2016.

kbench aims to extend kudb in both the number of test cases and hash table implementations under test.

[logo]: etc/kbench.png

# Results for the impatients

Data sorted by CPU time (unsigned keys, unsigned values)

Linux nuc 3.2.0-4-amd64 #1 SMP Debian 3.2.81-1 x86_64 GNU/Linux

| Rank | Implementation    | CPU (secs) | Memory (kB) |    #    | Notes     |
| ---- | ----------------- | ---------- | ----------- | ------- | --------- |
|    1 | khash             |      0.250 |      232524 |  625792 |           |
|    2 | ulib              |      0.270 |      232528 |  625792 |           |
|    3 | hhash             |      0.430 |      293472 |  625792 |           |
|    4 | ccan              |      0.520 |      227364 |  625792 |           |
|    5 | hashit-open       |      0.890 |      346448 |  625792 |           |
|    6 | hashit-overflow   |      0.890 |      415940 |  636334 | Bug here! |
|    7 | libevent          |      0.910 |      507340 |  625792 |           |
|    8 | gcc-libiberty     |      1.020 |      240048 |  625792 |           |
|    9 | python            |      1.070 |      264484 |  625792 |           |
|   10 | stb               |      1.100 |      232000 |  625792 |           |
|   11 | sys-glib          |      1.260 |      228372 |  625792 | *         |
|   12 | hashit-chain      |      1.280 |      300464 |  625792 |           |
|   13 | sys-tcl           |      1.350 |      256968 |  625792 | *         |
|   14 | tommyds           |      1.360 |      747724 |  625792 |           |
|   15 | c-algoritms       |      1.400 |      266592 |  625792 |           |
|   16 | c-hashtable       |      1.450 |      257076 |  625792 |           |
|   17 | uthash            |      1.460 |      618008 |  625792 |           |
|   18 | ghthash           |      1.560 |      362476 |  625792 |           |
|   19 | sys-apr           |      1.610 |      256592 |  625792 | *         |
|   20 | cfu               |      1.800 |      272364 |  625792 |           |
|   21 | generic-c-hashmap |      1.870 |      498700 |  630572 | Bug here! |
|   22 | sys-python        |      1.870 |      675476 |  625792 | *         |
|   23 | apr               |      1.910 |      253008 |  625792 |           |
|   24 | sglib             |      2.010 |      450564 |  625792 |           |
|   25 | htable            |      2.120 |      541136 |  625792 |           |
|   26 | ruby-st           |      2.280 |      255496 |  625792 |           |
|   27 | sys-LuaHashMap    |      2.280 |      281360 |  625792 | *         |
|   28 | st                |      2.730 |      245776 |  625792 |           |
|   29 | google-c-dense    |      3.550 |      244404 |  625792 |           |
|   30 | google-c-sparse   |      3.560 |      243912 |  625792 |           |
|   31 | sys-perl          |      4.910 |      694996 |  625792 | *         |

* Pre-installation of Debian System Libraries is required
