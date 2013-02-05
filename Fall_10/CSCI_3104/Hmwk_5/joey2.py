#!/usr/bin/python

import collections


def read_and_bin_words_by_len() :
    # read in words, and store it in a table by word length
    len_word_index = collections.defaultdict(list)

    fp = open("wordlist.txt")
    for line in fp :
        word = line.rstrip()
        len_word_index[len(word)].append(word)

    return len_word_index  


def alphabetize_string(string) :
    new_string = list(string)
    new_string.sort()
    return ''.join(new_string)


def collapse_bins(length_to_words) :
    length_to_collapsed_words = dict()
    for length, words in length_to_words.iteritems() :
        collapsed_words = map(lambda x: alphabetize_string(x), words)
        length_to_collapsed_words[length] = collapsed_words
    return length_to_collapsed_words


def get_candidate_parents(word) :
    candidates = list()

    for i in range(len(word)) :
        candidate = alphabetize_string(word[0:i] + word[i+1:])
        candidates.append(candidate)
    return candidates


def build_wordchain_dag(length_to_words):
    # create list of collapsed words indexed by length
    length_to_words_collapsed = collapse_bins(length_to_words)

    print length_to_words_collapsed

    # wordchain_dag is our DAG for doing DFS
    wordchain_dag = dict()
    # node_table is a utility table for looking up the pointers for each word
    node_table = dict()

    # build DAG
    for length, words in length_to_words.iteritems() :
        # iterate through from shortest words to longest words
        for word in words :
            print word
            collapsed_word = alphabetize_string(word)
    
            # create a node (dict) for our collapsed word 
            if not node_table.has_key(collapsed_word) :
                node_table[collapsed_word] = dict()
    
            length = len(word)
    
            if (length == 2) :
                # we will make 2-char words the top of the DAG
                wordchain_dag[collapsed_word] = node_table[collapsed_word]
            else :
                # get a list of all nodes with a length 1 character less than the current word
                if length_to_words_collapsed.has_key(length-1) :
                    parents = length_to_words_collapsed[length-1]
                else :
                    continue
    
                # get a list of possible permutations of the (i-1)st word
                candidates = get_candidate_parents(word)
    
                # iterate over all candidates to find parents to link to
                for candidate in candidates :
                    if candidate in parents :
                        # candidate appeared in list of parents, go ahead and make this word a child of the parent
                        node_table[candidate][collapsed_word] = node_table[collapsed_word]
                    
    return wordchain_dag, node_table
    

def dfs(node) :
    max_len = 0
    for word, child in node.iteritems() :
        print word
        child_len = dfs(child) + 1
        if child_len > len(word) :
            max_len = child_len
        else :
            max_len = len(word)
    return max_len


# create list of words indexed by length
length_to_words = read_and_bin_words_by_len()

# wordchain_dag is our DAG for doing DFS
wordchain_dag = dict()
# node_table is a utility table for looking up the pointers for each word
node_table = dict()

wordchain_dag, node_table = build_wordchain_dag(length_to_words)
                    
print wordchain_dag
print dfs(wordchain_dag)
