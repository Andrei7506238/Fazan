# Fazan Cheat RO
![Artboard 3PNG](https://user-images.githubusercontent.com/52383534/218466893-c75d93c7-7f2a-4a86-b23a-f483f69ad385.png)

Imagine having a secret weapon at your disposal in the game of [FAZAN](https://ro.wikipedia.org/wiki/Fazan_(joc)) - a cheat that can help you dominate your friends. The program will play aggressively and greedy, attempting to minimize the number of words the next opponent can propose. This way, you'll be able to block any chance of your opponent making a comeback and become truly invincible.

## Objectives
### Cheat Objectives:
- [x] The ability to load a word list based on the chosen game rules (base form (without diacritics) / inflectional form (with diacritics)), as well as the ability to load a custom word list (file name: custom.txt).
- [x] The ability to set the game rules according to preferences (whether or not the same word can be used multiple times - in which case the words said by other players, as well as the player's own word from the first round, can be memorized).
- [x] The program will signal words that do not exist in the word list or have already been used (according to the game rules).

### Trivia & Research Objectives
- [x] What is the maximum number of word in a game of Fazan in which no player is closed? (duplicate words are not accepted)
- [x] The list of words that can be used for closures, sorted by prefix [Forma Baza](rezultatCercetare/ListaCuvinteFolositeLaBlocareBaza.md) | [Forma Flexionara](rezultatCercetare/ListaCuvinteFolositeLaBlocareFlex.md)

## Demo:
![ezgif com-optimize](https://user-images.githubusercontent.com/115709086/219452636-b971f299-95b6-473c-8a3f-9ab39350ec72.gif)

## How to use:
Enter the word recived from the previous player in the input field. Press Enter and the word recommended will be written below.
If in the current game there are no duplicated words allowed check the ``remove typed words`` and ``remove recommended words`` to delete them from the internal data structure. In the first round (when there aren't any closures alowed) we might want to only delete the recived word without using the cheat to recomend a new one. In this case we might want to toggle off the ``Recommend words`` options. This is also useful if we play with more oponents and we want to eliminate the words they said.
We might chose to turn on/off ``check typed words`` to verify if the word said is valid.
 
## Technical info:
This project's most remarkable aspect is its underlying data structure: a directed multigraph based on a generalized adjacency matrix. The multigraph's nodes are identified by all possible 2-letter combinations, while edges connect a prefix node with a suffix node via a word. This configuration facilitates the creation of a matrix where each row corresponds to a prefix node, each column represents a suffix node, and each cell contains a list of words linking the two nodes.

To optimize performance, a secondary vector is utilized to track the outdegree of each node. Finding the outdegree of a node is a common operation and it can be computationally expensive.

The cheat mechanism operates by identifying the node Y with the smallest non-zero outdegree connected to the current user-entered word's suffix node X. Subsequently, the program returns one of the words found in the X→Y edge, utilizing a greedy and efficient approach. As it might not be as good as a minimax approach, more often than not the cheat instantly blocks the next opponent.

The challenge of finding the longest non-repeating word chain is equivalent to the problem of identifying a maximum-length simple path, [a task known to be NP-complete](https://en.wikipedia.org/wiki/Longest_path_problem#NP-hardness). Therefore, this project adopts a simple greedy heuristic algorithm that may not always produce the longest path. Nevertheless, the program's output remains a compelling and intriguing result. 

## Information regarding the word list:
- The current lists are modified versions of the Official List of Words allowed in Scrabble (LOC) available on dexonline:
- The Romanian diacritics from the inflectional list are replaced as follows: ("ă" - "~") ("î" - "^") ("â" - "#") ("ș" - ".") ("ț" - ",")
- Any other diacritics from other languages must be replaced with the corresponding form from the English alphabet (words like Führer become Fuhrer)
- To use a custom word list, create the custom.txt file in the directory with the executable file; One word per line; The rules regarding diacritics are the ones described above, available for the Romanian language.

## In the new release:
- Implemented a sleek and user-friendly graphical user interface (GUI) using Qt framework.
- Combined all the modes of operation into a single, streamlined mode that can be easily customized from a single page.
- Made significant improvements to the overall ease of use, making the application more accessible.
- The website visuals have been updated to be more visually appealing and the information has been revised to reflect the new version.
- The new regular expressions feature allows users to filter words and customize the cheat according to their specific rules and needs.
