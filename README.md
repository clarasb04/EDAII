# DATA STRUCTURES AND ALGORITHMS II, 2022-2023

# UPloFe ®

STUDENT NAMES: Pau Reig, Marc Rodriguez, Clara Serra, Roger Tomas

STUDENT NUMBERS: U215101, U215105, U204635, U214006

DATE OF SUBMISSION: 8 de juny de 2023

## PROJECT REPORT 
### TABLE OF CONTENTS
#### INTRODUCTION 
En el següent informe podran observar el treball de la nostra aplicació UPloFe. Una aplicació per trobar l’amor entre el gran ventall d’estudiants de la Universitat Pompeu Fabra. 

Ens vam voler inspirar, principalment, en la coneguda aplicació de cites Tinder. El seu funcionament és senzill; en la xarxa es van registrant els usuaris, els quals queden “classificats” per gustos i aficions, aquests gustos venen donats per un qüestionari realitzat al accedir a l’aplicació. Aquests usuaris poden interactuar entre ells creant vincles d’amistat enviant i rebent sol·licituds i realitzant publicacions en un mur el qual pot ser cercat per individualitat (un usuari en concret) o compartit (totes les publicacions realitzades).

El nostre principal objectiu era la creació d’una xarxa social per implementar en un àmbit que ens resultés familiar i quotidià, així doncs vam acabar centrant-nos en la vida universitària, donant lloc a una xarxa social per establir connexió amb gent com nosaltres, estudiants de la Pompeu Fabra, UPloFe. 

Al llarg del report podran anar observant el procés creatiu, estructural i realitzador del nostre projecte. Primerament parlarem dels objectius plantejats i els objectius assolits, donant peu a la nostra creativitat per generar noves funcionalitats per a la nostra xarxa, dividits en els objectius demandats, els objectius proposats i els objectius d’exploració. Seguidament una vista general però detallada de la nostra solució al plantejament dels objectius i del nostre codi per tal d’explicar-ne la funcionalitat i desenvolupament, donant també l’explicació dels errors trobats i com s’han plantejat les solucions.

### PROJECT OBJECTIVES 

#### Mandatory objectives met 

##### El primer objectiu és “Implementar com a mínim una Llista (List), una Pila (Stack) i una Cua (Queue) funcionals com a part d’alguna de les funcionalitats del projecte.”

La llista l’hem implementat per a guardar en un mateix lloc tots els usuaris existents en la xarxa, així també, podent reservar dinàmicament espai de memòria per a registrar-ne de nous. L’estructura està dividida en dos structs, així permetent-nos utilitzar una Double Linked List. El funcionament d’aquest algoritme es basa en usar un dels dos structs per a crear la llista de memòria dinàmica i l’altre per a poder-la recórrer.
Per a explicar el funcionament de la Double Linked List, hem de fer un previ amb la definició d’usuari i la possible navegació formant part de la xarxa.
Per tal de definir un usuari hem utilitzat una estructura typedef la qual té la següent forma:

![imatge1](EDAII/Imatges informe/1.png)

On sobrenom és el nickname escollit per l’usuari, guardat en un array de char (string); name i surname són el nom i el cognom de l’usuari, també guardats en forma de string; gmail és el correu electrònic amb el que es registra l’usuari, el domini del qual serà comprovat posteriorment, guardat en un array de char; població és la localitat de l’usuari guardat com a string; sexe és el gènere de l’usuari, guardat com a enter 1 si és home i 0 si és dona; edat és un enter que representa l’edat de l’usuari; gustos es tracta d’un array d’enters els quals representen les respostes del qüestionari que es realitza a l’entrar a l’aplicació, 1 en cas afirmatiu, 0 si la resposta és “no”; tant cua_sol com cua_amics són enllaços a les estructures per a implementar la Cua (queue), explicat més endavant; finalment, pub és un enllaç a la estructura publicació, per a poder controlar i estructurar les diferents publicacions que fagi cada usuari. 

L’estructura per a definir la Linked List és la següent:

# IMATGE

Així tenim situats el primer i últim usuari de la llista (per a saber l’espai de memòria a reservar necessari,) i la seva mida (size).

Per a desplaçar-nos al llarg de tota la llista tenim:

# IMATGE

L’estructura usuari és un puter que serà cada usuari que hi haurà a la linked list, i amb els enllaços next i prev podem realitzar el desplaçament.

TEMPS

Tres dies

LOCALITZACIÓ

Estructura: estructures.h línia 15-42; funció que crea linked list: usuari.c línia 63-83

La pila l’hem implementat a l’hora de presentar a l’usuari sol·licituds d’amistats aleatòries, on aquesta funció escull tres usuaris random entre tota la llista d’usuaris i li mostra a l’usuari en qüestió, deixant a lliure decisió si li vol enviar sol·licitud o no, així podrà conèixer a nous alumnes de l’universitat.

Una altra funció on hem implementat la pila, ha estat per mostrar les publicacions, on també escolleix aleatòriament 5 persones i mostra les seves publicacions més recents. Així, podem seguir l’ordre de la pila: LIFO (Last In First Out). És a dir, les publicacions més recents seran les primeres en ser mostrades.  Les dos funcions tenen la finalitat de mostrar gent nova i fer més ampli el cercle d’amistats.

L’estructura que hem utilitzat per la pila, ha estat la següent: dos enters, un que marca el top (l’últim element de la pila, és a dir, per on s’afegeixen i extreuen els valors) i la mida de la pila. També conté un punter d’user de llargada màxima de la pila. La seva implementació ha estat com la d’una array simple.

# IMATGE

Primerament hem inicialitzat la pila on l’hem creat i hem donat valor als diferents paràmetres (top -1 i size 10), hem codificat i implementat les funcions bàsiques d’una pila: la funció TOP, que proporciona l’últim usuari que ha entrat a la pila , la funció PUSH, que serveix per afegir un usuari a la pila, POP que serveix per treure l’últim usuari que ha estat introduit, IS_EMPTY per comprovar si està buida i IS_FULL per comprovar si està plena.

TEMPS

Cinc dies

LOCALITZACIÓ

Estructura: estructura.h línia 57-61; funcions principals de la pila: play.c 214-260; implementació de la pila en les sol·licituds aleatòries: play.c línia 15-44, implementació per mostrar les publicacions aleatòries: publicacions.c línia 101-117

La implementació de la cua l’hem utilitzat per controlar les amistats, afegir-les, enviar sol·licituds a altres usuaris, gestionar les sol·licituds pendents… Entre d’altres coses. L’hem implementat així per tal de que les primeres amistats (o sol·licituds) notificades siguin les primeres en ser ateses, seguint l’estructura de la cua, FIFO (First In First Out).

L’estructura que hem utilitzat per la cua ha estat un punter user a una array d’usuaris amb un màxim, que igual que en la pila té un màxim de 10 usuaris, i tres enters, un head per marcar la primera posició de la cua, un tail per marcar l'última posició ocupada de la cua per així, en el moment que tail > head, poder saber si la cua està plena, i la mida d’aquesta cua.

# IMATGE

També hem inicialitzat les dues cues (una per les amistats i l’altre per les sol·licituds d’amistat) que estructuren la informació de cada usuari. De la mateixa manera que hem treballat amb la pila, hem creat les funcions bàsiques: la funció CUA_BUIDA, per a comprovar si la cua està buida, la funció CUA_PLENA per a comprovar si la cua està plena, AFEGIR, per a afegir contingut a la cua, i TREURE per a treure el primer usuari afegit a la cua.

TEMPS

Tres dies

LOCALITZACIÓ

Estructura: estructures.h línia 45-50; funcions principals: play.c línia 113-154; funcions que utilitzen les funcions principals de la cua:play.c línia 61-108.

##### El segon objectiu: “Implementar funcionalment un dels algoritmes de búsqueda vist al curs (LinearSearch en el nostre cas)” 

Hem utilitzat l’algoritme de LinearSearch en una de les funcions del nostre codi. Aquesta funció s’encarrega de buscar el punter a un usuari a partir del sobrenom d’aquest i l’hem fet servir en diferents parts de codi, en diverses funcion, principalment per comprovar si un usuari existeix.

# IMATGE

El LinearSearch opera de la següent manera: es situa en el primer element (d’índex 0) de la llista i comprova si és l’element buscat, en cas afirmatiu, retorna l’índex de la posició en la que es troba l’element, en cas negatiu, accedeix a la següent posició de la llista (suma u al valor de l’índex). Repeteix aquest procediment fins arribar al final de la llista, i, en cas de que un cop recorreguda tota la llista no trobi l’element buscat, retorna un missatge comunicant-ho.

TEMPS

1 hora

LOCALITZACIÓ

Funció: play.c línia 159-169

##### El tercer objectiu: “Implementar funcionalment un dels algorismes d'ordenació que es veuran al llarg del curs (InsertionSort, BubbleSort, MergeSort o QuickSort). ”

L’algoritme que hem implementat en el nostre codi és el BubbleSort que l’hem utiltzat per ordenar el

# IMATGE

L’algoritme BubbleSort actua de la següent manera:

Inicia l’ordenació en la primera posició de la llista, comparant el seu valor amb el de la següent posició de la llista. En cas de que el primer sigui més gran que el segon, els intercanvia de posició. En cas contrari mantenen les seves posicions. Així es desplaça fins al final de la llista. Aquest procés l’itera tantes vegades com sigui necessari per a tenir al llista ordenada.

TEMPS

2 hores

LOCALITZACIÓ

Funció: usuari.c línia 87-110, utilització: usuari.c línia 82

##### El quart objectiu: “Implementar o bé un Diccionari (Dictionary) o bé una taula Hash (HashTable) funcionals”

Hem implementat un Diccionari que funciona amb una Taula Hash per tal de poder tenir un recompte dels temes més comuns entre les publicacions dels diferents usuaris de l’aplicació. Hem creat una rànquing amb les deu paraules més utilitzades tenint en compte els titulars de les publicacions.

Per poder codificar el diccionari hem creat dues estructures. L’estructura node dels diferents elements del diccionari conté la clau, el valor de cada clau i un punter cap al següent node. L’altra estructura hash_table és per tenir la mida del diccionari i un punter capa els diferents nodes del diccionari, com si es tractés d’una “array”. 

# IMATGE

Llavors, hem creat les funcions bàsiques que necessita un diccionari que està implementat amb una hash table. La funció HASH per determinar la posició on va cada node depenen de la seva clau, CREATE_NODE per crear l’espai per un node, ADD_DICT per afegir les diferents claus i en el cas de que ja existeixin incrementar-li el valor, per tal de portar un recompte per saber quina paraula és la més comú entre les publicacions, i la funció TOP_10 que, com hem comentat anteriorment, mostra el rànquing dels 10 temes més publicats. 

Per últim, com que utilitzem mèmoria dinàmica per crear els diferents nodes, després de cada execució alliberem el diccionari i alliberem la memòria, utilitzant la funció FREE_DICT. Així doncs, quan iniciem sessió es crea el diccionari i es miren totes les publicacions i quan sortim de l’aplicació s’allibera la memòria reservada pel diccionari.

TEMPS
Dos dies
LOCALITZACIÓ
Estructura: estructures.h línies 63-73; funcions principals: publicacions.c línies 136-177, 225-235; implementació: publicacions.c línies 180-222


##### El cinquè objectiu: “Totes les parts importants del teu codi han d'estar comentades”

Com es pot observar en el nostre treball, tot el codi està comentat en detall per facilitar la comprensió per qualsevol lector i també per expressar el que volem fer en cada funció.

TEMPS: 
No hi ha temps concret durant la creació de cada funció
LOCALITZACIÓ -


##### El sisè objectiu: “Utilitzar github perquè tots els membres de l'equip puguin treballar alhora i més còmodament”

Des d’un primer moment, hem estat utilitzat la plataforma github, tot i això, vam tenir problemes dificultant-nos pujar el codi. Finalment, l’hem hagut de penjar manualment cada cop que feia modificacions. É per això que no ho penjavem cada dia que fèiem modificacions, sinó només quan teniem una bona part realitzada. A més a més, l’hem compaginat amb la funció de compartir sessió de programació contenida en el propi CLion.

TEMPS -
LOCALITZACIÓ -

#### Desirable objectives met 

Els objectius desitjables que hem realitzat han estat els següents:

##### El primer objectiu: “Llegir dades d’una font externa com un arxiu de text o CSV (No implica desat de dades)” 

L’hem implementat en el moment d’obtenir les dades dels usuaris les quals estan guardades en documents de text (.txt). Aquestes dades són les de registre de sessió dels usuaris (usuari-contrasenya), les dades de l’enquesta inicial (de l’estructura usuari) i el mur de publicacions realitzades per cada usuari. 


# IMATGE

Exemple d’un arxiu .txt de lectura

Per tal de poder llegir els documents hem utilitzat funcions com la següent:

# IMATGE

Amb la qual comprovem primer si el fitxer s’ha obert correctament o no i posteriorment emmagatzemem les dades de cadascun dels usuaris a la llista, estructurant-les amb user.

TEMPS

Aproximadament cinc dies

LOCALITZACIÓ

Els .txt es troben dins la carpeta de cmake-build-debug, llegir fitxer usuaris: usuari.c línia 114-130; llegir fitxer publicacions: publicacions.c línia 63-93; llegir fitxer pins: main.c línia 110-129.

##### El segon objectiu: “Seria molt interessant que la Xarxa Social sigués temàtica i tingués una capa de personalització a nivell conceptual que la faci més especial entre els altres projectes.”

Per a aquest objectiu hem pensat que, tot i inspirar-nos en algunes xarxes socials ja creades, la nostra és especial i única ja que es centra en un àmbit: l’universitari, concretament el que ens toca més a prop, ja que ens situem en l’Universitat Pompeu Fabra. Això li dona una impremta diferent a les altres, ja que és de fàcil i quotidiana implementació. A més l’hem creat per conèixer nova gent de l’Universitat per formar noves amistats o amors.

TEMPS

Dos hores 

LOCALITZACIÓ -

#### Exploratory objectives met 

Implementar les funcionalitats de lectura i desament de dades (Informació dels usuaris i els seus contactes, i altres que es vulgui afegir) des d'un fitxer extern (.txt o csv)”

Com hem comentat anteriorment hem utilitzat fitxers .txt per ser llegits i llavors, aquests matexios fitxer els hem utilitzat per guardar informació. 

Hem utilitzat quatre fitxers de text. El primer per guardar els usuaris amb les seves respectives contrasenyes pins. Llavors, quan s'obre l’aplicació, es mostra l’opció d’iniciar sessió amb un usuari i una contrasenya que seran llegits i comprovats al fitxer, i també es mostra l’opció de registrar-se i crear un nou usuari. Per tant, es guarden les noves dades del sobrenom i el pin en aquest fitxer i, a més a més, es guarden totes les dades de l’usuari nou registrat en un altre fitxer. Aquest, és el fitxer d’usuaris on hi ha el nom, cognom, sobrenom, edat, sexe, gmail, població, gustos… 

Quan estem dins de l’aplicació, es crea la linked list mitjançant aquest document que va llegint i va afegint cada usuari a la linked list. Després, les publicacions també les guarden en un .txt que, quan es tanca la sessió, s’actualitza per què aquestes no siguin simplement espontànies. A més, el document està creat perquè cada usuari sols tingui 5 publicacions i es sapigui quin usuari fa cada publicació. 

TEMPS

3 dies 

LOCALITZACIÓ

Els fitxers són els mateixos esmentats anteriorment i es troben a la carpeta cmake-build-debug; funció per guardar dades del fitxer usuaris: usuari.c línia 134-148; funció per guardar les dades de les publicacions: publicacions.c línia 37-61 i  per guardar dades del fitxer pins: main.c línia 132-154.


### SOLUTION

#### System Architecture

L’estructura del codi es basa en una varietat de funcions que es van cridant entre elles i que van modificant l’array d’usuaris principalment o la utilitzant per fer certes funcionalitats.

Comencem per la funció main(), on es comença a executar el codi. Dins d’aquesta tenim la inicialització de la llista d’usuaris i del diccionari. Després es fa la baixada de dades dels fitxers dels usuaris i de les publicacions, que van omplint les dades de les estructures que ja tenim inicialitzades. Un cop tot inicialitzat i omplert amb les dades ja existents passem a una funció que serveix per iniciar sessió a un dels usuaris existents de la llista o crear un usuari nou per poder accedir a la xarxa social. Si entrem amb un usuari ja existent ens demanarà el pin d’aquest usuari i comprovarà que corresponguin ambdós. 

A l’altre cas, quan crees un usuari nou, pregunta per les seves dades personals i el correu el qual es comprova que contingui el domini de la universitat. Després de preguntar per les dades ens demana que contestem un qüestionari sobre els nostres gustos per poder omplir el perfil. L’usuari ja s’afegeix a la llista d’usuaris inicialitzada. Si ho fem correctament ja entrem dins de les funcionalitats de la xarxa amb la funció recursiva menu().  

Funció menu()

Dins aquesta funció tenim les diferents opcions que l’usuari pot fer:

1. Mirar el llistat d’usuaris

2. Interactuar amb usuaris i publicacions

3. Tancar sessió per accedir amb un altre usuari+

4. Sortir

Dins de la primera opció hi trobem una funció que ens imprimeix tots els usuaris registrats a la xarxa social. Ens diu la informació bàsica de cada un. 

A la segona opció hi trobem de nou com un segon menú amb moltes més opcions. Aquí dins trobem la funcionalitats de sol·licituds d'amistat i de les publicacions. A la mateixa funció accedim a un d’aquests dos mòduls. I la tercera i quarta opció ja són per sortir de la xarxa social o per canviar d’usuari. Ara expliquem amb més detall que hi trobem dins de la funció interactuar:

Publicacions

A les publicacions ens trobem diferents funcions per cobrir totes les necessitats. Les funcions ens permeten afegir publicacions al usuari amb el qual hem iniciat sessió, mirar les publicacions d’un usuari i mirar les últimes publicacions de tots els usuaris. 

Sol·licituds

Les sol·licituds s’estructuren en una cua on hi trobem les últimes sol·licituds d’amistat rebudes. L’usuari hi troba tres opcions d’accessibilitat: enviar sol·licituds d’amistat, mostrar usuaris aleatoris per triar si li envies sol·licitud o no i gestionar les teves sol·licituds d’amistat pendents. 

Amb això ja tenim totes les funcions que fa la nostra xarxa social. Per acabar hi tenim les funcions fora del menu() que s’executen un cop aquest acaba. Aquestes funcions s’encarreguen de tornar a guardar les dades als fitxers .txt, amb les dades noves que s’han creat i així no perdre la informació. 

#### Error Handling 

Durant el treball, ens hem trobat amb diferents problemes que hem tingut d’anar resolent poc a poc. 

En un principi no teniem molt clar com havíem d’encadenar els diferents arxius .h i .c, això ens ocasionava un gran problema, ja que no podíem compilar el codi perquè tots els arxius s’intentaven obrir alhora. Vam trigar molta estona per poder resoldre aquest problema, però mentrestant anàvem programant per tal de no perdre gaire el temps. Per afrontar aquest problema vam necessitar un petit cop de mà del professor, però a partir d’aquí va anar tot sobre rodes. De totes maneres ens vam trobar amb petites dificultats, però amb dedicació i hores anàvem trobant els diferents errors que ens donava el codi, molts d’ells ocasionats per lectura i desament de les dades en els documents .txt.

El fet de no quedar-nos de braços plegats i, paral·lelament als errors de compilació, continuar programant les funcions restants ha estat un avantatge i un inconvenient, doncs anàvem avançant, però quan ja vam poder executar-les, no funcionaven, és a dir, potser no produïen errors, però no realitzaven la tasca esperada. Per tal de localitzar els errors hem anat posant prints dins de les funcions errònies, d’aquesta manera, hem anat veient el punt concret on errava en l'execució. Un cop ubicat el tros de codi incorrecte l’analitzavem fins trobar l’error concret o substituïem la secció de codi per una altra. En ocasions, corregint errors vam fer servir l’eina proporcionada per CLion, el debugger. Aquesta eina ens ha permès veure els error dins de la cua, les llistes enllaçades…

Pel que fa al maneig dels possibles errors dels usuaris, durant l’execució del programa hem utilitzat bucles (while) amb la finalitat de, si en la tria d’opcions s’introdueixen respostes equivocades, es demani que es repeteixi la resposta fins ser coincident amb una de les opcions esperades.

#### Data model design

# IMATGE

#### Dataset description and processing 

Les dades de la xarxa social es guarden en fitxers .txt. Aquests fitxers segueixen una estructura exacte que el codi, quan s’inicia la xarxa social, pugui llegir correctament. Primer de tot, tenim un fitxer que conté la llista d’usuaris i tota la informació necessària d’aquests. 

# IMATGE

Imatge de la llista d’usuaris en el fitxer usuaris.txt

Amb la funció llegir_fitxer() anem recorrent el fitxer i obtenint les dades dels usuaris. El que fa el codi és obtenir tota la linia de dades (cada linia correspon a un usuari), i després anem separant les dades que anem llegint a les diferents variables de la llista i de l’usuari. La funció crida a una altre que s’encarrega d’afegir aquest usuari a la llista i modificar tots els paràmetres pertinents. El codi d’aquesta funció és:

# IMATGE

Si passem a la llegida de dades de les publicacions ens trobem un fitxer amb una estructura un amica més complexa. Aquest fitxer s’estructura de la manera següent, primer de tot trobem l’usuari del qual anem a llegir les publicacions. Un cop passada aquesta línia trobem una lletra que ens diu si hi ha publicacions o no en aquella posició, és a dir, tindrem cinc N o F, ja que un usuari pot tenir fins a 5 publicacions . Si trobem una F es que hi ha publicació i si trobem una N significa que no trobem cap publicació en aquella posició i que hem de seguir llegint. En cas que trobem una F significa que a les línies següents hi trobarem primer el títol i després el cos de la publicació. El fitxer acaba sent així:

# IMATGE

La funció que llegeix aquest fitxer (llegir_fitx()) primer llegeix el usuari i amb la funció buscar() troba el punter a aquest usuari, per això és important que aquesta funció es cridi després de la funció que crea la llista. Després busca la F o N que indiqui si ha de llegir una publicació o no. En cas que si entra dins un if i es busca el títol i el cos de la publicació en el fitxer. En cas que no la funció seguirà llegint les N que faltin fins passar al següent usuari. Això ho repetirà fins a acabar els usuaris. El codi d’aquesta funció és el següent:

# IMATGE

Amb aquestes dos funcions ja llegim les dades que tenim guardades en fitxers. Pel procés contrari, quan hem de guardar-les de tornada als fitxers, tenim dos funcions que accedeixen de nou al fitxer, però en el mode escriptura i tornen a escriure totes les dades als fitxers seguint aquestes estructures per poder llegir-ho correctament. Les funcions que s’encarreguen d’això són: guardar_publ() per les publicacions i omplir_fitxer() pels usuaris. 

### REFERENCES 

Powerpoint Aula Global EDA II.
