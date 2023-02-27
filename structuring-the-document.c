#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

struct word {
    char* data;
};

struct sentence {
    struct word* data;
    int word_count;//denotes number of words in a sentence
};

struct paragraph {
    struct sentence* data  ;
    int sentence_count;//denotes number of sentences in a paragraph
};

struct document {
    struct paragraph* data;
    int paragraph_count;//denotes number of paragraphs in a document
};

/*-------------------------------------------------------------------
 * Update the Error has been resolved. 
 * It was as we suspected plus a bunch more.
 * ------------------------------------------------------------------
 *
 * Error is in the get_* functions we defined.
 * possibly in the start stop variables, look into it.
 *
 * ------------------------------------------------------------------
 * 			Expected Output:
 * ------------------------------------------------------------------
 *
 * 	Learning pointers is more fun.It is good to have pointers.
	Learning C is fun
   	Learning

 * ------------------------------------------------------------------
 * 		      Sample input with error:
 * ------------------------------------------------------------------
 *
 * 	2
	Learning C is fun.
	Learning pointers is more fun.It is good to have pointers.

	get_document: 2

	get_paragraph: 1

	get_sentence: 3

	get_word count: 9 | Learning

	get_word count: 2 | C

	get_word count: 3 | is
	3
	1 2

	Sentence count: 0

	2 1 1

	Word count: 3
	Learning  C  is
	3 1 1 1
	Learning
 * ------------------------------------------------------------------
 */

struct word get_word(char *text, int start, int stop){
    struct word w;
    int count = stop-start+1;

    // printf("\nget_word count: %d start: %d stop: %d |", count, start, stop);

    w.data=(char*)malloc((count+1)*sizeof(char));
    int j=0;
    for(int i=start; i<=stop; i++) w.data[j++] = text[i];
    w.data[j] = '\0';
    
    // printf(" %s\n", w.data);
    
    return w;
}
struct sentence get_sentence(char* text, int start, int stop){
    struct sentence sen;
    sen.word_count=1;
    
    for(int i=start; i<=stop; i++) if(text[i] == ' ') sen.word_count++;
    sen.data=(struct word*)malloc(sen.word_count*sizeof(struct word));
    
    // printf("\nget_sentence | wcount: %d start: %d stop: %d\n", sen.word_count, start, stop);
    
    int word_start=start, word_stop=start, j=0;
    for(int i=start; i<=stop; i++){
        word_stop=i-1;
        if(text[i] == ' '){
            sen.data[j++] = get_word(text, word_start, word_stop);
            word_start=i+1;
        }
    }
    sen.data[j] = get_word(text, word_start, word_stop+1);
    return sen;
}
struct paragraph get_paragraph(char* text, int start, int stop){
    struct paragraph para;
    para.sentence_count=0;
    
    for(int i=start; i<=stop; i++) if(text[i] == '.')para.sentence_count++;
    para.data=(struct sentence*)malloc(para.sentence_count*sizeof(struct sentence));
    
    // printf("\nget_paragraph | count: %d start:%d stop:%d\n", para.sentence_count, start, stop);
    
    int para_stop=start, para_start=start, j=0;
    for(int i=start; i<=stop; i++){
        if(text[i] == '.'){
            para_stop=i-1;
            para.data[j++] = get_sentence(text, para_start, para_stop);
            para_start = i+1;
        }
    }
    return para;    
}
struct document get_document(char* text) {
    struct document doc;
    doc.paragraph_count=1;
    
    for(int i=0; i<strlen(text); i++) if(text[i] == '\n') doc.paragraph_count++;
    doc.data = (struct paragraph*)malloc(doc.paragraph_count*sizeof(struct paragraph));
    
    // printf("\nget_document: %d\n", doc.paragraph_count);
    
    int start = 0, stop = 0, j=0;
    for(int i=0; i<strlen(text); i++){
        stop=i-1;
        if(text[i]=='\n'){            
            doc.data[j++] = get_paragraph(text, start, stop);
            start=i+1;
        }
    }
    doc.data[j] = get_paragraph(text, start, stop+1);
    return doc;

}
struct word kth_word_in_mth_sentence_of_nth_paragraph(struct document Doc, int k, int m, int n) {
    struct word w;
    struct paragraph p = Doc.data[n-1];
    struct sentence s = p.data[m-1];
    w = s.data[k-1];
    return w;
}

struct sentence kth_sentence_in_mth_paragraph(struct document Doc, int k, int m) {
       struct sentence s;
       struct paragraph p = Doc.data[m-1];
       s = p.data[k-1];
       s.word_count= p.data[k-1].word_count;
       
       return s;
}

struct paragraph kth_paragraph(struct document Doc, int k) {
    struct paragraph p;
    p = Doc.data[k-1];
    p.sentence_count = Doc.data[k-1].sentence_count;
    
    return p;
}





void print_word(struct word w) {
    printf("%s", w.data);
}

void print_sentence(struct sentence sen) {
	
	// printf("\nWord count: %d\n", sen.word_count);

    for(int i = 0; i < sen.word_count; i++) {
        print_word(sen.data[i]);
        if (i != sen.word_count - 1) {
            printf(" ");
        }
    }
}

void print_paragraph(struct paragraph para) {
	
	// printf("\nSentence count: %d\n", para.sentence_count);
	
    for(int i = 0; i < para.sentence_count; i++){
        print_sentence(para.data[i]);
        printf(".");
    }
}

void print_document(struct document doc) {
	
	// printf("\nParagraph count: %d\n", doc.paragraph_count);

    for(int i = 0; i < doc.paragraph_count; i++) {
        print_paragraph(doc.data[i]);
        if (i != doc.paragraph_count - 1)
            printf("\n");
    }
}

char* get_input_text() {	
    int paragraph_count;
    scanf("%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    getchar();
    for (int i = 0; i < paragraph_count; i++) {
        scanf("%[^\n]%*c", p[i]);
        strcat(doc, p[i]);
        if (i != paragraph_count - 1)
            strcat(doc, "\n");
    }

    char* returnDoc = (char*)malloc((strlen (doc)+1) * (sizeof(char)));
    strcpy(returnDoc, doc);
    return returnDoc;
}

int main() 
{
    char* text = get_input_text();
    struct document Doc = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            struct word w = kth_word_in_mth_sentence_of_nth_paragraph(Doc, k, m, n);
            print_word(w);
        }

        else if (type == 2) {
            int k, m;
            scanf("%d %d", &k, &m);
            struct sentence sen= kth_sentence_in_mth_paragraph(Doc, k, m);
            print_sentence(sen);
        }

        else{
            int k;
            scanf("%d", &k);
            struct paragraph para = kth_paragraph(Doc, k);
            print_paragraph(para);
        }
        printf("\n");
    }     
}
