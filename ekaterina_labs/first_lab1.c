#include <stdio.h>

int get_len(char line[]) {
	int count = 0;
	while (line[count] != '\0') {
		count++;
	}
	return count;
}


int check_word(char word_words[], char word_src[]) {
	if (get_len(word_words) != get_len(word_src)) {
		return 1;
	}
	else {
		int len = get_len(word_src);
		for (int i = 0; i < len; i++) {
			if (word_src[i] != word_words[i]) {
				return 1;
			}
		}
	}
	return 0;
}


int find_word(char word_src[], char words[]) {
	for (int i = 0; i < get_len(words); i++) {
		if (words[i] != ' ') {

			char word_words[256];
			word_words[0] = words[i];
			for (int j = i + 1; words[j] != ' ' && words[j] != '\0'; j++) {

				word_words[j - i] = words[j];
				word_words[j - i + 1] = '\0';
			}

			if (check_word(word_words, word_src) == 0) {
				return 1;
			}

			i += get_len(word_words) - 1;
		}
	}
	return 0;
}


int delete_words(char src[], char words[]) {
	char new_line[256];
	new_line[0] = '\0';

	int count_del = 0;
	if (get_len(src) == 1 || get_len(words) == 1) {
		return 0;
	}

	for (int i = 0; i < get_len(src); i++) {
		if (src[i] != ' ') {

			char word_src[256];
			word_src[0] = src[i];
			for (int j = i + 1; src[j] != ' ' && src[j] != '\0'; j++) {

				word_src[j - i] = src[j];
				word_src[j - i + 1] = '\0';
			}

			int len_word = get_len(word_src);
			if (find_word(word_src, words) == 0) {
				int start = get_len(new_line);
				if (start != 0) {
					new_line[start] = ' ';
					new_line[start + 1] = '\0';
					for (int k = 0; k < get_len(word_src); k++) {
						new_line[start + 1 + k] = word_src[k];
						new_line[start + k + 2] = '\0';
					}
				}
				else {
					for (int k = 0; k < get_len(word_src); k++) {
						new_line[k] = word_src[k];
						new_line[k + 1] = '\0';
					}
				}
			}
			else {
				count_del += 1;
			}


			i += len_word - 1;
		}
	}
	for (int i = 0; i < get_len(new_line); i++) {
		src[i] = new_line[i];
		src[i + 1] = '\0';
	}
	return count_del;
}

int main()
{
	char src[256];
	char words[256];

	printf("Enter src: ");
	fgets(src, 256, stdin);
	src[get_len(src) - 1] = '\0';

	printf("Enter words: ");
	fgets(words, 256, stdin);
	words[get_len(words) - 1] = '\0';

	int count_del = delete_words(src, words);

	printf("\n\n\nCount deleted words: %d\n", count_del);
	printf("New line: %s\n", src);


}