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

More about every option and how the cheat works can be found in the wiki.


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
