#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_TABLE_SIZE 100

typedef struct HashNode {
  char *key;
  char *value;
  struct HashNode *next;
} HashNode;

typedef struct HashTable {
  HashNode *nodes[HASH_TABLE_SIZE];
} HashTable;

unsigned int hash(char *key) {
  unsigned int hash = 5381;
  int c;
  while ((c = *key++))
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  return hash % HASH_TABLE_SIZE;
}

void hash_table_insert(HashTable *table, char *key, char *value) {
  unsigned int index = hash(key);
  HashNode *node = malloc(sizeof(HashNode));
  node->key = strdup(key);
  node->value = strdup(value);
  node->next = table->nodes[index];
  table->nodes[index] = node;
}

char *hash_table_lookup(HashTable *table, char *key) {
  unsigned int index = hash(key);
  HashNode *node = table->nodes[index];
  while (node) {
    if (strcmp(node->key, key) == 0)
      return node->value;
    node = node->next;
  }
  return NULL;
}

void hash_table_delete(HashTable *table, char *key) {
  unsigned int index = hash(key);
  HashNode *node = table->nodes[index];
  HashNode *prev = NULL;
  while (node) {
    if (strcmp(node->key, key) == 0) {
      if (prev)
        prev->next = node->next;
      else
        table->nodes[index] = node->next;
      free(node->key);
      free(node->value);
      free(node);
      return;
    }
    prev = node;
    node = node->next;
  }
}

void hash_table_save(HashTable *table, const char *filename) {
  FILE *fp = fopen(filename, "w");
  if (!fp) {
    perror("Error opening file");
    return;
  }

  int count = 0;
  for (int i = 0; i < HASH_TABLE_SIZE; i++) {
    HashNode *node = table->nodes[i];
    while (node) {
      count++;
      node = node->next;
    }
  }

  fwrite(&count, sizeof(int), 1, fp);

  for (int i = 0; i < HASH_TABLE_SIZE; i++) {
    HashNode *node = table->nodes[i];
    while (node) {
      fwrite(node->key, strlen(node->key) + 1, 1, fp);
      fwrite(node->value, strlen(node->value) + 1, 1, fp);
      node = node->next;
    }
  }

  fclose(fp);
}

void hash_table_load(HashTable *table, const char *filename) {
  FILE *fp = fopen(filename, "r");
  if (!fp) {
    perror("Error opening file");
    return;
  }

  int count;
  fread(&count, sizeof(int), 1, fp);

  for (int i = 0; i < count; i++) {
    char key[1024];
    char value[1024];
    fread(key, 1024, 1, fp);
    fread(value, 1024, 1, fp);
    hash_table_insert(table, key, value);
  }

  fclose(fp);
}


int main() {
  HashTable table;
  memset(table.nodes, 0, sizeof(table.nodes));

  hash_table_insert(&table, "key1", "value1");
  hash_table_insert(&table, "key2", "value2");
  hash_table_insert(&table, "key3", "value3");

  printf("%s\n", hash_table_lookup(&table, "key1"));
  printf("%s\n", hash_table_lookup(&table, "key2"));
  printf("%s\n", hash_table_lookup(&table, "key3"));

  hash_table_delete(&table, "key2");

  printf("%s\n", hash_table_lookup(&table, "key1"));
  printf("%s\n", hash_table_lookup(&table, "key2"));
  printf("%s\n", hash_table_lookup(&table, "key3"));

  hash_table_save(&table, "table.dat");

  HashTable loaded_table;
  memset(loaded_table.nodes, 0, sizeof(loaded_table.nodes));
  hash_table_load(&loaded_table, "table.dat");

  printf("%s\n", hash_table_lookup(&loaded_table, "key1"));
  printf("%s\n", hash_table_lookup(&loaded_table, "key2"));
  printf("%s\n", hash_table_lookup(&loaded_table, "key3"));

  return 0;
}




