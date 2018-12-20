# Journal de bord du Capitaine Dobby


* ## Vendredi 14 décembre 2018
> Après l'attaque du corsaire Alexander Lawrence Mccormack, le Wati Water a subit de lourds dégâts.
> Mon précieux navire s'est échoué sur une île inconnue (que je vais nommer... euh... Aile-Ef) et nous voilà coincés ici.
> Tout ceci promet d'être long, moussaillons !

*Prise de connaissance de la doc*

* ## Lundi 17 décembre 2018
> En tant que capitaine, j'ai affecté les premières tâches vitales pour notre survie. Ces bons à rien
> n'y comprendront sûrement rien, je les jetterais aux manchots !

*Répartition des taches et organisation en binomes*


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

*Correction des erreurs et poursuite du développement*

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

*Factorisation et poursuite du développement*

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
    
    
* ## Jeudi 20 décembre 2018 [... A FINIR]

*Poursuite du développement de la phase 1. On n'avait pas compris la différence entre sh_strtab et strtab nous faisant alors perdre beaucoup de temps.*

  * __Marius et Clément :__
    * Automatisation des tests.
    * Correction et terminaison de la table des symboles.
    
  * __Stephen et Laura :__
    * Correction de diverses erreurs et création d'un schéma pour mieux comprendre.
    * Modification de elf_section_content.* (séparation entre lecture et affichage du contenu).

  * __Aurélien et Joris :__
    * 

    
