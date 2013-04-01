C++-Oblig2_Tic-Tac-Toe
======================


###Oppgavetekst:
#### 1. *N-på-rad*, fritt frem
Denne oppgaven passer for de som ønsker mer vekt på algoritmiske problemstillinger. Her skal du implementere en generalisert versjon av 3-på-rad (bondesjakk, tic-tac-toe), over terminal - menneske mot maskin. Den klassiske varianten er slik:

1. Det er to spillere, og et spillbrett på 3 x 3 ruter
2. Det trekkes tilfeldig hvem som skal starte
3. Den som starter plasserer en brikke, deretter plasserer nestemann, og så videre.
4. Vinneren er den som først får 3 på rad, horisontalt, vertikalt eller diagonalt. 
5. Dersom det er umulig å få 3 på rad er det uavgjort.

I 4 på rad er det helt like regler, men tallet 3 er erstattet med 4. Du skal implementere spillet, men med mulighet for n x n spill, minst opp til 8 x 8, altså "8 på rad", men gjerne høyere. Max n avgjøres av ditt ambisjonsnivå.

Følgende gjelder:

- Brukeren skal bli bedt om å oppgi et tall mellom 3 og n, der n er minst 8.

- Spillet skal starte iht. reglene over. 

- Det bør skrives ut en matrise med spillets tilstand mellom hvert trekk. Bruk gjerne X og O som betegnelse på brikkene, eller vær kreativ hvis du vil.

- Brukeren kan gjerne oppgi sitt trekk som et koordinat, "x,y", der x er en av [A,B,C,…] og y en av [1,2,3, …], eller du kan finne på noe mer brukervennlig hvis du ønsker.

- Denne oppgaven krever potensielt mindre C++-spesifike ferdigheter, så det legges defor enda større vekt på at programmet kjører fint uten store feil, og generell spillbarhet.

- En nødløsning for deg som sliter: Implementer først 3 og så 4 på rad i denne oppgaven, så har du noe å levere…

- Ekstra (frivillig) utfordring: lag programmet ditt slik at du kan sette maskinen til å spille mot seg selv - eller til å spille mot en annens strategi, og la det være mulig å vise spillet i sakte film i terminalen, slik at man som bruker kan følge med. Sett gjerne ditt program til å spille mot en medstudent sitt - da må dere bli enige om en api. OBS: Dersom du gjør dette, si fra!

###Ferdig:

	- Gameboard, scaler fint uansett størrelse. har testet med 100x100.
	- Score, virker som det fungerer fint, har testet med 20x20. 
	- Human vs Human, funker
	- Human vs Bot, funker
	- Bot vs Bot, funker

###To-Do:

- skrive om game() så det funker med nytt namespace og nye klasser.
- game.cpp->Game()  Fungerer hvem som starter først riktig?
- Bot vs noen annens ai
- Make Kompilering, husk echo med kommandoen for å kompilere
- teste på studssh :P