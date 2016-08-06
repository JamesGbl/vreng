/****************************************************************************
 *                             VREL COMPONENTS                              *
 *                                                                          *
 *                           Copyright (C) 2000                             *
 *     Yanneck Chevalier, Pascal Belin, Alexis Jeannerod, Julien Dauphin    *
 *                                                                          *
 *   This program is free software; you can redistribute it and/or modify   *
 *   it under the terms of the GNU General Public License as published by   *
 *   the Free Software Foundation; either version 2 of the License, or      *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   This program is distributed in the hope that it will be useful,        *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU General Public License for more details.                           *
 ****************************************************************************/

#include "vrel.hpp"
#include "aoi.hpp"
#include "box.hpp"
#include "error.hpp"
#include "datalist.hpp"


// Constructeur de la classe Aoi 
Aoi::Aoi()
{
  options_box();
}

// M�thode exec de la classe Aoi 
void Aoi::exec (Data_liste * env1)
{
  if (env1->nb_data != 8) Erreur("Aoi needs 8 arguments");
  fprintf(yyout, "<aoi pos=\"%.2f %.2f %.2f %.2f\" channel=\"%s\"> <solid shape=\"box\" dim=\"%.2f %.2f %.2f\"", 
	  env1->donnee[0]->get_float(),
	  env1->donnee[1]->get_float(),
	  env1->donnee[2]->get_float(),
	  env1->donnee[3]->get_float(),
	  env1->donnee[7]->nom,
	  env1->donnee[4]->get_float(),
	  env1->donnee[5]->get_float(),
	  env1->donnee[6]->get_float());
  ecrire_box();
  fprintf(yyout, " />");
  fprintf(yyout, "</aoi>\n");
}
