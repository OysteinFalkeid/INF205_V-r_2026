# Oppgave 3

- Øystein Falkeid
- Venuga Sivarajah
- gruppe 11

## oppgave 2.1

<!-- <small>

Implementer en lenket datastruktur for grafer; det er en datastruktur som består av noder og kanter, der hver kant er en tilknytning mellom to noder. Grafene skal være rettede (asymmetriske), med kanter som er ordna, dvs. at en kant går fra en node til en annen node med en viss retning.

Hver node og hver kant skal bli tilordna en std::string som dataelement. Datastrukturen dere skal bruke til å implementere dette er insidenslister, dvs. at både noder og kanter er objekter, og hvert av disse objektene har som et av medlemmene sine ei liste over alle de andre objektene det har ein direkte tilknytning (insidens) til. Den lista kan m.a. være ei lenket liste eller en dynamisk datatabell. Insidens er definert slik at det er et forhold mellom noder og kanter (i motsetning til naboskap mellom par av noder).

Strengverdiene til nodene skal være unike; dvs. at en node kan identifiseres gjennom den verdien den har blitt utstyrt med. Strengverdiene til kantene er ikke-unike.

Det er mulig for start- og målnoden til en kant å være den samme; det er også lov å ha flere kanter mellom de samme start- og målnodene.

Grunnfunksjonaliteten omfatter å tilføye en kant:

    void insert_edge(std::string node_a_label, std::string edge_label, std::string node_b_label);

Der er node_a_label identifikatoren til startnoden, edge_label strengverdien til kanten og node_b_label identifikatoren til målnoden. Med dette skal en ny kant opprettes som objekt, og ved behov, dvs. om og bare om de ikke ennå finnes, skal noder med verdi node_a_label og henholdsvis node_b_label også opprettes som nye objekter.

Blir diskutert 11.3. av gruppe 13 og 22.

</small> -->

## oppgave 2.2

<!-- <small>
Koden skal kunne lese og skrive filer i et format som:

    node_a_label edge_label node_b_label.
    node_a_label edge_label node_b_label.
    node_a_label edge_label node_b_label.

</small> -->


## oppgave 2.3

<!-- <small>
Innfør en abstrakt klasse som grensesnittdefinisjon, og gjør den implementeringen dere begynte med ovenfor, til en konkret subklasse.

</small> -->

## oppgave 2.4

<!-- <small>

Legg til en annen implementering av grensesnittet. Denne gangen bruk en nabomatrise (adjacency matrix) som datastruktur, dvs. en 2D-datatabell der verdien nabo[i][j] indiserer om og hvordan node i er knyttet til j. Ved den datastrukturen er det bare nodene som er objekter, mens kantene blir representert av matrisen.

Obs: Det at grafen kan være asymmetrisk, innebærer at matrisen kan være asymmetrisk. Som enkeltverdi i matrisen bør vi bruke noe slikt som ei liste over streng-verdier e.l., siden vi kan ha flere kanter mellom de samme nodene, og hver kant er utstyrt med en std::string.

</small> -->


## oppgave 2.5

<!-- <small>

Implementer følgende:

    void disconnect(std::string node_a_label, std::string node_b_label);
    void remove_node(std::string node_label);

Der skal disconnect slette alle kanter fra node_a_label til node_b_label, og bare i den retningen; remove_node skal slette en node, og dermed alle kantene som denne noden var insident til.

I begge tilfeller skal koden sjekke om det har oppstått isolerte noder, som ikke lenger er knyttet til noe, og så slette alle slike noder.

</small> -->

## oppgave 2.6

<!-- <small>


Implementer alle de fem elementene av en containerdatastruktur etter femmerregelen.

</small> -->


## oppgave 3.1

<!-- <small>

Implementer Tarjans algoritme (en variant av dybde-først-søk) for å beregne de sterkt sammenhengende komponentene av grafen.

Koden skal innlese grafen i trippelnotasjon som ved problemliste 2.

Bruk grensesnittet slik at de samme algoritmene kan kjøres med den lenkede og den matrisebaserte grafdatastrukturen. Programmet bør kunne få flagg fra kommandolinjen som gjør det stille/pratsomt (silent/verbose mode). [Dette gjelder også problem 3.2.]

Eksempelinput: graph-benchmark-scc.cpp og scc-graph-benchmark-data.zip.

</small> -->


## oppgave 3.2

<!-- <small>

Implementer en algoritme som identifiserer alle nodepar (ni, nj) slik at det både er en sti r0-r2-r4…-r(2m-2) og en sti r1-r3-r5…-r(2m-1) fra node ni til node nj. Det betyr at den første kanten på den ene stien har "r0" som påskrift (dvs. assosiert strengverdi), den andre kanten "r2", osv., slik at noden med påskrift "ni" er insident til den første kanten, mens den siste kanten på stien er insident til den noden med påskrift "nj". Samtidig er det også en annen sti mellom de samme nodene ni og nj der kantene er påskrevne "r1", "r3" osv.

I tillegg til selve grafen skal denne koden få en fil som input som representerer forespørselen i følgende form:

    r0 r2 r4 r6.
    r1 r3 r5 r7.

Obs: Vi bruker unike nodepåskrifter, men ikke-unike kantepåskrifter.

Eksempelinput: graph-benchmark.cpp og knowledge-graph-benchmark-data.zip.

</small> -->


## oppgave 3.3

<!-- <small>

Utstyr makefilen med kommandoer for demo-programkall som skal kunne kjøres med GNU make på følgende måte:

    make pro22  // demonstrerer problem 2.2
    make pro25  // demonstrerer problem 2.5
    make pro31  // demonstrerer problem 3.1
    make pro32  // demonstrerer problem 3.2

Obs: Det skal ikke ta altfor lang tid å kjøre demoscenarioene.

</small> -->


## oppgave 3.4

<!-- <small>

Bruk grafgeneratorene graph-benchmark.cpp og graph-benchmark-scc.cpp til å måle det gjennomsnittlige tidskravet til algoritmene for de to problemene ovenfor, i kombinasjon med de to grafdatastrukturene, som funksjon av problemstørrelsen, som er antallet n på noder i grafen. Analyser skaleringsatferda og visualiser den som diagrammer.

Ved diamantstiproblemet gir det mening å undersøke to forskjellige skaleringsscenarioer: (a) Konstant lengde m av stiene; (b) stilengde m proporsjonal med nodetallet n.

</small> -->


## oppgave 3.5

<!-- <small>

Tegn et ER-diagram som representerer deres data-/klassestruktur.

</small> -->

## Oppgave 3.6

<!-- <small>

Inkluder et kort sammendrag (med avsnittstitler som tilsvarer problem 2.1 til 3.5) i PDF format; lengde 3 sider maks.

</small> -->
