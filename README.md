# VUT-FIT-PROJECT-IZP-project_2-2024-2025
## Projekt 2 - Práce s datovými strukturami

### Popis projektu
Vytvořte program, který v daném monochromatickém obrázku hledá nejdelší vodorovné a svislé úsečky a největší čtverce. Obrázek je uložen jako bitmapa v textovém souboru ve formě obdélníkové matice nul a jedniček. Cílem programu je výpis počáteční a koncové souřadnice nalezené úsečky nebo čtverce.

### Překlad a odevzdání zdrojového souboru
Odevzdání: Program implementujte ve zdrojovém souboru figsearch.c.
Překlad: Program překládejte s následujícími argumenty:

    cc -std=c11 -Wall -Wextra -Werror figsearch.c -o figsearch

### Syntax spuštění
    ./figsearch --help
nebo
    ./figsearch test SOUBOR
nebo
    ./figsearch hline SOUBOR
nebo
    ./figsearch vline SOUBOR
nebo
    ./figsearch square SOUBOR

argumenty programu:
- **--help** způsobí, že program vytiskne nápovědu používání programu a skončí.
- **test** pouze zkontroluje, že soubor daný druhým argumentem programu obsahuje řádnou definici bitmapového obrázku. V případě, že formát obrázku odpovídá definici (viz níže), vytiskne "Valid" (na stdout). V opačném případě (např. ilegálních znaků, chybějících údajů nebo špatných hodnot) program tiskne "Invalid" (na stderr).
- **hline** v daném obrázku nalezne a vytiskne počáteční a koncovou souřadnici první nejdelší horizontální úsečky.
- **vline** v daném obrázku nalezne a vytiskne počáteční a koncovou souřadnici první nejdelší vertikální úsečky.
- **square** v daném obrázku nalezne a vytiskne počáteční a koncovou souřadnici prvního největšího čtverce.
- **SOUBOR** reprezentuje jméno souboru s obsahem bitmapy.

**Bitmapa** daného rasterového obrázku je uložena v textovém souboru obsahující číselné údaje oddělené bílými znaky. První dva číselné údaje reprezentují velikost obrázku v počtu pixelů (výška a šířka obrázku - tedy počet řádků a počet sloupců). Následují definice jednotlivých řádků (oddělené bílým znakem), kde každý řádek obsahuje barevné hodnoty jednotlivých pixelů. Každý pixel má hodnotu buď 0 (bílá) nebo 1 (černá). Počáteční souřadnice 0, 0 reprezentuje levý horní roh. Souřadnice jsou v pořadí index řádku, index sloupce.

**Horizontální/vertikální úsečka** je nepřerušená posloupnost sousedících černých pixelů na stejném řádku/sloupci. Je definovaná prvním a posledním bodem úsečky, tj. počáteční a koncovou souřadnicí daných bodů. Každá souřadnice je definována dvojicí indexů řádku a sloupce. Počáteční souřadnice má index řádku/sloupce menší než nebo roven indexu řádku/sloupce koncové souřadnice.

**Nejdelší horizontální/vertikální úsečka** je taková horizontální/vertikální úsečka, která pokrývá největší počet pixelů.

**Největší čtverec** je taková posloupnost sousedících černých pixelů, která na obrázku tvoří obvod čtverce, který pokrývá co největší pole. Počáteční souřadnice čtverce je souřadnice jeho levého horního bodu a koncová souřadnice čtverce je souřadnice jeho pravého dolního bodu.

V případě, že na obrázku existuje více útvarů se stejnou největší velikostí, program tiskne pouze souřadnice prvního z nich. **První úsečka nebo čtverec** obsahuje pixel co nejblíže nahoře vlevo -- tedy s co nejmenším indexem řádku a v případě nejednoznačnosti i s co nejmenším indexem sloupce.

### Implementační detaily
Tisk souřadnic proveďte na jeden řádek ve formátu "R1 C1 R2 C2", kde R1,C1 označuje číslo řádku a sloupce počáteční souřadnice a R2,C2 je koncová souřadnice. Pokud soubor neobsahuje žádný černý pixel, tiskne se v případě hledání útvarů "Not found".

### Příklad vstupů a výstupů bitmapy
Textový soubor *obrazek.txt* s obsahem:

4 5
0 0 1 1 1
0 0 1 0 1
1 0 1 1 1
1 1 1 1 1

reprezentuje bitmapový obrázek o 4 řádcích a 5 sloupcích s podobou takovou, že 0 reprezentují prázdné pole a 1 pole zaplněné

### Příklady spuštění
První nejdelší horizontální úsečka začíná na pozici 3 0 (řáden 3, sloupec 0) a končí na pozici 3 4:

    ./figsearch hline obrazek.txt
    3 0 3 4

První nejdelší vertiální úsečka začíná na pozici 0 2 (řádek 0, sloupec 2) a končí na pozici 3 2:

    ./figsearch vline obrazek.txt
    0 2 3 2

První největší čtverec začíná na pozici 0 2 a končí na pozici 2 4:

    ./figsearch square obrazek.txt
    0 2 2 4

### Nápověda
- Vytvořte si datový typ Image pro uložení monochromatického obrázku.
- Implementujte funkci pro načtení obrázku včetně ověření validity dat.
- Implementujte funkci pro získání barvy na zadaných souřadnicích.
- Implementujte algoritmy pro hledání obrazců; každý algoritmus ve vlastní funkci. Algoritmus obdrží parametrem obrázek a nalezené souřadnice vrátí v parametrech předaných odkazem.

### Hodnocení
10/14