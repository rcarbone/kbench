#include <stdio.h>
#include <stdint.h>

#include "benchmark.h"

/* The implementation */
#include "judyLArray.h"
#include "judySArray.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

typedef judyLArray <JudySlot, judyvalue> hashtable_int_t;
typedef judySArray <judyvalue> hashtable_str_t;

static unsigned judyL_count (hashtable_int_t * ht)
{
  unsigned count = 0;
  judyLArray <JudySlot, judyvalue>::pair nxt = ht -> begin ();
  while (nxt . value)
    {
      count ++;
      nxt = ht -> next ();
    }
  return count;
}


static unsigned judyS_count (hashtable_str_t * ht)
{
  unsigned count = 0;
  judySArray <judyvalue>::pair nxt = ht -> begin ();
  while (nxt . value)
    {
      count ++;
      nxt = ht -> next ();
    }
  return count;
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

int udb_int (int n, const unsigned * keys)
{
  hashtable_int_t * ht = new hashtable_int_t;
  unsigned i;
  unsigned count = 0;

  for (i = 0; i < n; i ++)
    {
      if (ht -> find (keys [i]))
	ht -> removeEntry (keys [i]);
      else
	ht -> insert (keys [i], i + 1);
    }

  count = judyL_count (ht);

  ht -> clear ();
  delete ht;

  return count;
}


int udb_str (int n, char * const * keys)
{
  hashtable_str_t * ht = new hashtable_str_t (255);
  unsigned i;
  unsigned count = 0;

  for (i = 0; i < n; i ++)
    {
      if (ht -> find (keys [i]))
	ht -> removeEntry (keys [i]);
      else
	ht -> insert (keys [i], i + 1);
    }

  count = judyS_count (ht);

  ht -> clear ();
  delete ht;

  return count;
}


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str);
}
