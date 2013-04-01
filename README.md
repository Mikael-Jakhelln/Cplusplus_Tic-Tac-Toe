C++-Oblig2_Tic-Tac-Toe
======================


###Oppgavetekst:
#### 1. *N-p�-rad*, fritt frem
Denne oppgaven passer for de som �nsker mer vekt p� algoritmiske problemstillinger. Her skal du implementere en generalisert versjon av 3-p�-rad (bondesjakk, tic-tac-toe), over terminal - menneske mot maskin. Den klassiske varianten er slik:

1. Det er to spillere, og et spillbrett p� 3 x 3 ruter
2. Det trekkes tilfeldig hvem som skal starte
3. Den som starter plasserer en brikke, deretter plasserer nestemann, og s� videre.
4. Vinneren er den som f�rst f�r 3 p� rad, horisontalt, vertikalt eller diagonalt. 
5. Dersom det er umulig � f� 3 p� rad er det uavgjort.

I 4 p� rad er det helt like regler, men tallet 3 er erstattet med 4. Du skal implementere spillet, men med mulighet for n x n spill, minst opp til 8 x 8, alts� "8 p� rad", men gjerne h�yere. Max n avgj�res av ditt ambisjonsniv�.

F�lgende gjelder:

- Brukeren skal bli bedt om � oppgi et tall mellom 3 og n, der n er minst 8.

- Spillet skal starte iht. reglene over. 

- Det b�r skrives ut en matrise med spillets tilstand mellom hvert trekk. Bruk gjerne X og O som betegnelse p� brikkene, eller v�r kreativ hvis du vil.

- Brukeren kan gjerne oppgi sitt trekk som et koordinat, "x,y", der x er en av [A,B,C,�] og y en av [1,2,3, �], eller du kan finne p� noe mer brukervennlig hvis du �nsker.

- Denne oppgaven krever potensielt mindre C++-spesifike ferdigheter, s� det legges defor enda st�rre vekt p� at programmet kj�rer fint uten store feil, og generell spillbarhet.

- En n�dl�sning for deg som sliter: Implementer f�rst 3 og s� 4 p� rad i denne oppgaven, s� har du noe � levere�

- Ekstra (frivillig) utfordring: lag programmet ditt slik at du kan sette maskinen til � spille mot seg selv - eller til � spille mot en annens strategi, og la det v�re mulig � vise spillet i sakte film i terminalen, slik at man som bruker kan f�lge med. Sett gjerne ditt program til � spille mot en medstudent sitt - da m� dere bli enige om en api. OBS: Dersom du gj�r dette, si fra!

###Ferdig:

	- Gameboard, scaler fint uansett st�rrelse. har testet med 100x100.
	- Score, virker som det fungerer fint, har testet med 20x20. 
	- Human vs Human, funker
	- Human vs Bot, funker
	- Bot vs Bot, funker

###To-Do:

- skrive om game() s� det funker med nytt namespace og nye klasser.
- game.cpp->Game()  Fungerer hvem som starter f�rst riktig?
- Bot vs noen annens ai
- Make Kompilering, husk echo med kommandoen for � kompilere
- teste p� studssh :P