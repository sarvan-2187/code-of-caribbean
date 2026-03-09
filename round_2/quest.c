#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
    char s[10001];
    scanf("%s", s);
    
    int len = strlen(s);
    
    // Store patterns and their frequencies
    typedef struct {
        char pattern[4];
        int freq;
    } Pattern;
    
    Pattern patterns[10000];
    int num_patterns = 0;
    
    // Extract all 3-letter patterns and count frequencies
    for (int i = 0; i <= len - 3; i++) {
        char pattern[4];
        strncpy(pattern, &s[i], 3);
        pattern[3] = '\0';
        
        // Find or create pattern entry
        int found = -1;
        for (int j = 0; j < num_patterns; j++) {
            if (strcmp(patterns[j].pattern, pattern) == 0) {
                found = j;
                break;
            }
        }
        
        if (found == -1) {
            strcpy(patterns[num_patterns].pattern, pattern);
            patterns[num_patterns].freq = 1;
            num_patterns++;
        } else {
            patterns[found].freq++;
        }
    }
    
    // Check validity and find max frequency of valid patterns
    int max_freq = 0;
    
    for (int p = 0; p < num_patterns; p++) {
        int is_valid = 1;
        
        // Check if this pattern appears at consecutive positions (i and i+3)
        for (int i = 0; i <= len - 6; i++) {
            if (strncmp(&s[i], patterns[p].pattern, 3) == 0 &&
                strncmp(&s[i+3], patterns[p].pattern, 3) == 0) {
                is_valid = 0;
                break;
            }
        }
        
        // Include frequency only if pattern is valid
        if (is_valid && patterns[p].freq > max_freq) {
            max_freq = patterns[p].freq;
        }
    }
    
    printf("%d\n", max_freq);
    
    return 0;
}
