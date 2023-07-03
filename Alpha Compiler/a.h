struct alpha_token_t{
                int line;
                int num;
                char * quote;  // quote
                char * categ;  // kathgoria
                char * id;  // kefalea 
                char * type;  // typos metavliths
                struct alpha_token_t * next;
        };