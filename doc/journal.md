# Journal de bord du Capitaine Dobby


* ## Vendredi 14 décembre 2018
> Après l'attaque du corsaire Alexander Lawrence Mccormack, le Wati Water a subit de lourds dégâts.
> Mon précieux navire s'est échoué sur une île inconnue (que je vais nommer... euh... Aile-Ef) et nous voilà coincés ici.
> Tout ceci promet d'être long, moussaillons !

*Prise de connaissance de la doc.*

* ## Lundi 17 décembre 2018
> En tant que capitaine, j'ai affecté les premières tâches vitales pour notre survie. Ces bons à rien
> n'y comprendront sûrement rien, je les jetterai aux manchots !

*Répartition des taches et organisation en binomes.*

  * __Marius et Clément :__
    * Rédaction du fichier .h contenant les structures et les types nécessaires ( elf_types.h ).
    * Affichage de la table des sections (elf_section.c, elf_section.h).

  * __Stephen et Laura :__
    * Lecture du header (elf_header.c, elf_header.h).

  * __Aurélien et Joris :__
    * Affichage du header (read-header.c).


* ## Mardi 18 décembre 2018
> L'abri a bien avancé, mais il faut maintenant le ranger. Certains matelots finissent de monter leur tente de fortune.
> Moi, Capitaine Dobby, je m'enrichis de ce que mes matelots me rapportent. J'ai divisé l'île en sections, et en explorant
> les lieux, j'ai découvert des symboles cabalistiques disséminés un peu partout !

*Correction des erreurs et poursuite du développement.*

  * __Marius :__
    * Organisation des dossiers et renommage des fichiers pour respecter une standardisation.
    * Ecriture d'un Makefile.

  * __Clément :__
    * Poursuite du développement de l'affichage de la table des sections (read-section-table.c).

  * __Stephen et Laura :__
    * Séparation de elf_types.h afin que chaque elf_type_*.h corresponde à une étape.
    * Correction de elf_header.c, les soucis rencontrés concernaient l'endianess des fichiers lus.
      * Rédaction de fread.c, fread.h prenant en compte l'endianess.
    * Affichage du contenu d'une section (elf_section_content.c, elf_section_content.h, read-section-content.c).

  * __Aurélien et Joris :__
    * Terminaison et correction de read-header.c.
    * Affichage de la table des symboles (elf_symbol.c, elf_symbol.h).

* ## Mercredi 19 décembre 2018
> Mes matelots n'ont pas bien travaillé ! Ils passent une bonne partie de la journée à réparer les murs de l'abri qui
> s'écroulent ! Et pour couronner le tout, nous avons été attaqués par diverses créatures ! Satanés saigfolteux !
> Ce séjour forcé s'annonce compliqué...

*Factorisation et poursuite du développement.*

  * __Marius et Clément :__
    * Affichage des tables de réimplantation (prototypes).
    * Factorisation et correction de read-header.c (fonctions mises dans elf_header.c).

  * __Stephen et Laura :__
    * Affichage des tables de réimplantation.
    * Modification du Makefile.

  * __Aurélien et Joris :__
    * Poursuite du développement de l'affichage de la table des symboles.

  * __Stephen et Marius :__
    * Factorisation et aération du Makefile.
    * Correction de read-relocation


* ## Jeudi 20 décembre 2018
> J'ai enfin déchiffré les étranges symboles de l'île ! La dernière pièce du puzzle se cachait dans une petite grotte
> encore inexplorée. Je vais peut-être pouvoir découvrir les secrets que renferment ces lieux. Mes hommes, eux, ont
> consolidé l'abri. Il devrait tenir par tous temps désormais.

*Poursuite du développement de la phase 1. On n'avait pas compris la différence entre sh_strtab et strtab nous faisant alors perdre beaucoup de temps. De plus l'utilisation de la commande valgrind nous indique que tous nos programmes sont exempts de fuite mémoire.*

  * __Marius et Clément :__
    * Automatisation des tests.
    * Correction et terminaison de la table des symboles.

  * __Stephen et Laura :__
    * Correction de diverses erreurs et création d'un schéma pour mieux comprendre.
    * Modification de elf_section_content.* (séparation entre lecture et affichage du contenu).

  * __Aurélien et Joris :__
    * Embellissement du code.

* ## Vendredi 21 décembre 2018
> L'abri étant terminé, les réparations du bateau ont pu commencées. C'est encore un peu chaotique, mais je vais mettre de
> l'ordre dans tout ça. Et je n'hésiterai pas à donner des coups de bâton si le chantier n'avance pas assez rapidement
> à mon goût.

*Prise de connaissance de la phase 2 et répartition des taches.*

  * __Marius et Clément :__
    * Automatisation des tests, compréhension de la phase 2.

  * __Stephen et Laura :__
    * Mise en mémoire des sections (dans elf_section_content.c).

  * __Aurélien et Joris :__
    * Suppression des sections REL et RELA (réécriture de la table des entêtes de section dans rewrite_section_table.c).

* ## Lundi 7 janvier 2019
> Enfin libre ! Je respire ! Cela faisait deux semaines que j'étais coincé dans une grotte de l'autre côté de l'île.
> Et que vois-je en revenant au camp ? Un ramassis de fainéants allongés sur le sable les pieds en éventails, pas même
> un peu inquiets de la disparition de leur capitaine. Quelle bande d'ingrats ! Il va falloir leur rappeler que je ne
> les paie pas à lambiner.

*Poursuite du développement (et de la compréhension) de la phase 2.*

  * __Marius et Clément :__
    * Automatisation des tests (sabrage de la sortie de grepp).
    * Test des fuites mémoires.
    * Mise en place de la représentation mémoire du fichier (fusion de tous les types).

  * __Stephen et Laura :__
    * Correction des fuites mémoires.

* ## Mardi 8 janvier 2019
> Aujourd'hui, les réparations du bateau ont plutôt bien avancées. Mon fidèle voilier commence à reprendre forme ! Mais
> j'ai peur que les travaux prennent du retard. La maladie a touché une partie de l'équipage et notre docteur est
> complètement dépassé. Si on ne se dépêche pas, cette île va finir par avoir notre peau.

*Poursuite du développement de la phase 2.*

  * __Marius et Clément :__
    * Automatisation des tests.
    * Fonctions de correction des symboles.

  * __Stephen et Laura :__
    * Organisation de la renumérotation des sections.
    * Écriture des structures modifiées dans un fichier de sortie.

* ## Mercredi 9 janvier 2019
> En suivant la piste des symboles de l'île, je me suis finalement retrouvé au pied d'une pierre sur laquelle était
> gravé un texte. Mais les symboles y étaient arrangés bizarrement. Je n'avais encore jamais rien vu de tel. Impossible
> d'en comprendre le sens ! Je vais tenter de déchiffrer ça pendant que mes hommes finissent de réparer mon navire. 

*Poursuite du développement de la phase 2; rédaction du rapport, finalisation de l'automatisation des tests.*

  * __Marius et Clément :__
    * Finalisation de l'automatisation des tests.
    * Automatisation des tests de fuites mémoires.
    * Finalisation de la correction des symboles.
    * Étude des relocations.
    * Modification de l'organisation des fichiers.

  * __Stephen et Laura :__
    * Écriture du rapport.
    * Gestion des options pour Load-Elf-file.c.
    * Gestion d'erreurs pour Load-Elf-file.c.
    * Adressage des sections. 
    
  * __Aurélien et Joris :__
    * Compréhension et utilisation d'automake/autoconf.
