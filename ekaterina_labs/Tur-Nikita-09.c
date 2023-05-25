#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define T 32

typedef struct _chaining {
	char* str;
	struct _chaining *prev, *next;
} chaining;


typedef struct _chaining_table {
	int size;
	int (*hash)(char*);
	chaining** chains;
} chaining_table;


int hash_xor_l1(char *str) {
	int s = 0;
	for (int i = 0; i < strlen(str); i++) {
		s ^= str[i];
		s <<= 1;
	}
	return s % T;
}


chaining_table* create_chaining_table(int size, int (*hash)(char*)) {
	chaining_table* ct = (chaining_table *)calloc(1, sizeof(chaining_table));
	ct->size = size;
	ct->hash = hash;
	ct->chains = (chaining **)calloc(size, sizeof(chaining *));
	return ct;
}


int add_ct(char* data, chaining_table* ct) {
	int h = ct->hash(data);
	if (h < ct->size) {
		chaining *ch;
		if (ch = ct->chains[h]) {
			while (ch->next) ch = ch->next;
			ch->next = (chaining*)calloc(1, sizeof(chaining));
			ch->next->prev = ch;
			ch = ch->next;
		}
		else {
			ch = ct->chains[h] = (chaining*)calloc(1, sizeof(chaining));
		}
		ch->str = strdup(data);
		return 1;
	}
	return 0;
}


int remove_ct(char* data, chaining_table* ct) {
	int h = ct->hash(data);
	if (h < ct->size) {
		chaining* ch;
		if (ch = ct->chains[h]) {
			while (ch) {
				if (!strcmp(ch->str, data)) {
					if (ch->prev) ch->prev->next = ch->next;
					if (ch->next) ch->next->prev = ch->prev;
					free(ch->str);
					free(ch);
					return 1;
				}
				ch = ch->next;
			}
		}
	}
	return 0;
}


int contains_ct(char* data, chaining_table* ct) {
	int h = ct->hash(data);
	if (h < ct->size) {
		chaining* ch;
		if (ch = ct->chains[h]) {
			while (ch) {
				if (!strcmp(ch->str, data)) {
					return 1;
				}
				ch = ch->next;
			}
		}
	}
	return 0;
}


void print_ct(chaining_table* ct) {
	for (int i=0;i<ct->size;i++) {
		printf("Index: %02d\n", i);
		chaining* ch;
		if (ch = ct->chains[i]) {
			while (ch) {
				printf("  %s", ch->str);
				ch = ch->next;
			}
			printf("\n");
		}
	}
}


typedef struct _oa {
	int exist;
	char* str;
} oa;


typedef struct _oa_table {
	int size;
	int (*hash)(char*);
	int (*probe)(int, int);
	oa * chains;
} oa_table;


oa_table *create_oa_table(int size, int (*hash)(char*), int (*probe)(int, int)) {
	oa_table* ct = (oa_table*)calloc(1, sizeof(oa_table));
	ct->size = size;
	ct->hash = hash;
	ct->probe = probe;
	ct->chains = (oa *)calloc(size, sizeof(oa));
	return ct;
}


int add_oat(char* data, oa_table* ct) {
	int h = ct->hash(data);
	if (h < ct->size) {
		int h2 = h, n=0;
		do {
			oa* om = om = ct->chains + h2;
			if (!om->exist) {
				if (om->str) free(om->str);
				om->str = strdup(data);
				om->exist = 1;
				return 1;
			}
			h2 = ct->probe(h2, ++n);
		} while (h != h2);
	}
	return 0;
}


int remove_oat(char* data, oa_table* ct) {
	int h = ct->hash(data);
	if (h < ct->size) {
		int h2 = h, n = 0;
		do {
			oa* om = om = ct->chains + h2;
			if (om->exist && !strcmp(om->str, data)) {
				om->exist = 0;
				return 1;
			}
			h2 = ct->probe(h2, ++n);
		} while (h != h2);
	}
	return 0;
}


int contains_oat(char* data, oa_table* ct) {
	int h = ct->hash(data);
	if (h < ct->size) {
		int h2 = h, n = 0;
		do {
			oa* om = om = ct->chains + h2;
			if (om->exist && !strcmp(om->str, data)) {
				return 1;
			}
			h2 = ct->probe(h2, ++n);
		} while (h != h2);
	}
	return 0;
}


void print_oat(oa_table* ct) {
	oa* om = om = ct->chains;
	for (int i = 0; i < ct->size; i++, om++) {
		printf("Index: %02d ", i);
		if (om->exist) {
			printf("  %s", om->str);
		}
		printf("\n");
	}
}


int inv_linear(int pos, int i) {
	if (++pos == T) pos = 0;
	return pos;
}


int inv_square(int pos, int i) {
	pos += (i + i * i) / 2;
	return pos % T;
}


void action_key(const char* action) {
	printf("%s\n", action);
}


void next_key() {
	printf("---\n");
	printf("Press a key to continue...\n\n");
	getc(stdin);
}

int main() {
	char buff[8];

	action_key("create chaining table...");
	chaining_table* ct = create_chaining_table(T, hash_xor_l1);
	for (int i = 0; i < T*2; i++) {
		sprintf(buff, "sss%02d", i);
		add_ct(buff, ct);
	}
	

	action_key("print chaining table...");
	print_ct(ct);
	next_key();


	action_key("find...");
	if (contains_ct("sss10", ct)) {
		printf("sss10 in table\n");
	}
	if (!contains_ct("sss88", ct)) {
		printf("sss88 not in table\n");
	}
	next_key();


	action_key("delete...");
	remove_ct("sss10", ct);
	if (!contains_ct("sss10", ct)) {
		printf("sss10 not in table\n");
	}
	next_key();

	
	action_key("print after delete...");
	print_ct(ct);
	next_key();


	action_key("create open addressing table with linear function...");
	oa_table* ot = create_oa_table(T, hash_xor_l1, inv_linear);
	for (int i = 0; i < T/2; i++) {
		sprintf(buff, "sss%02d", i);
		add_oat(buff, ot);
	}

	action_key("print...");
	print_oat(ot);
	next_key();


	action_key("find...");
	if (contains_oat("sss10", ot)) {
		printf("sss10 in table\n");
	}
	if (!contains_oat("sss88", ot)) {
		printf("sss88 not in table\n");
	}
	next_key();


	action_key("delete...");
	remove_oat("sss10", ot);
	if (!contains_oat("sss10", ot)) {
		printf("sss10 not in table\n");
	}
	next_key();


	action_key("print after delete...");
	print_oat(ot);
	next_key();


	action_key("create open addressing table with square function...");
	ot = create_oa_table(T, hash_xor_l1, inv_square);
	for (int i = 0; i < T / 2; i++) {
		sprintf(buff, "sss%02d", i);
		add_oat(buff, ot);
	}

	action_key("print...");
	print_oat(ot);
	next_key();


	action_key("find...");
	if (contains_oat("sss10", ot)) {
		printf("sss10 in table\n");
	}
	if (!contains_oat("sss88", ot)) {
		printf("sss88 not in table\n");
	}
	next_key();


	action_key("delete...");
	remove_oat("sss10", ot);
	if (!contains_oat("sss10", ot)) {
		printf("sss10 not in table\n");
	}
	next_key();


	action_key("print after delete...");
	print_oat(ot);
	next_key();
}
