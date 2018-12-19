# Journal de bord du capitaine Dobby


* ## Vendredi 14 décembre 2018
*Prise en connaissance de la doc*


* ## Lundi 17 décembre 2018
*Répartition des taches et organisation en binomes*

  * __Marius et Clément :__
    * Rédaction du fichier .h contenant les structures et les types nécessaires ( elf_types.h ).
    * Affichage de la table des sections (elf_section.c, elf_section.h).
    
  * __Stephen et Laura :__
    * Lecture du header (elf_header.c, elf_header.h).
    
  * __Aurélien et Joris :__
    * Affichage du header (read-header.c).
    
    
* ## Mardi 18 décembre 2018
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
    
* ## Mercredi 19 décembre 2018... __[à compléter]__
*Factorisation et poursuite du développement*

  * __Marius et Clément :__
    * Affichage des tables de réimplantation.
    * Factorisation de read-header.c.
    
  * __Stephen et Laura :__
    * Affichage des tables de réimplantation.
  
  * __Aurélien et Joris :__
    * Poursuite du développement de l'affichage de la table des symboles.
    
    
