
/* Permutations of keys and types */
#define OBJ_INT_INT   1               /* keys -> integers and values -> integers */
#define OBJ_STR_INT   2               /* keys -> strings and values -> integers  */


/* Objects allocation based on type */
#define mkobj_int_int(x) mkobj (x, OBJ_INT_INT, NULL)
#define mkobj_str_int(x) mkobj (0, OBJ_STR_INT, x)

/* The objects in the hash table */
typedef struct obj obj_t;
struct obj
{
  char type;
  unsigned ukey;           /* unsigned key */
  char * skey;             /* string key   */
  unsigned uval;           /* unsigned val */
  char * sval;             /* string val   */
  obj_t * pval;            /* pointer val  */

  unsigned uhash;          /* hashed unsigned key */
  unsigned shash;          /* hashed string key   */

  tommy_node _reserved_;   /* field required to make the object hash-able */
};

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

static obj_t * mkobj (unsigned n, char type, char * str)
{
  obj_t * obj = calloc (1, sizeof (* obj));

  switch (obj -> type = type)
    {
    case OBJ_INT_INT:
      obj -> ukey = n;
      obj -> uval = n * 2;
      obj -> uhash = tommy_inthash_u32 (obj -> ukey);
      break;
    case OBJ_STR_INT:
      obj -> skey = strdup (str);
      obj -> uval = n * 2;
      obj -> uhash = tommy_hash_u32 (0, obj -> skey, strlen (obj -> skey));
      break;
    }
  return obj;
}


static void rmobj (obj_t * obj)
{
  if (! obj)
    return;
  if (obj -> skey)
    free (obj -> skey);
  if (obj -> sval)
    free (obj -> sval);
  free (obj);
}


static obj_t ** setup_int_objs (unsigned n, const unsigned * keys)
{
  obj_t ** objs = calloc (n, sizeof (* objs));
  unsigned i;

  for (i = 0; i < n; i ++)
    objs [i] = mkobj_int_int (keys [i]);
  return objs;
}


static obj_t ** setup_str_objs (unsigned n, char * const * keys)
{
  obj_t ** objs = calloc (n, sizeof (* objs));
  unsigned i;

  for (i = 0; i < n; i ++)
    objs [i] = mkobj_str_int (keys [i]);
  return objs;
}


static void teardown (unsigned n, obj_t ** objs)
{
  unsigned i;
  for (i = 0; i < n; i ++)
    rmobj (objs [i]);
  free (objs);
}
