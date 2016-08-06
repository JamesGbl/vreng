/******************************************************************************
 *                                                                            *
 *                               VREL COMPONENTS                              *
 *                                                                            *
 *                           Copyright (C) 2000                               *
 *                                                                            *
 *     Yanneck Chevalier, Pascal Belin, Alexis Jeannerod, Julien Dauphin      *
 *                                                                            *
 *                                                                            *
 *    This program is free software; you can redistribute it and/or modify    *
 *    it under the terms of the GNU General Public License as published by    *
 *    the Free Software Foundation; either version 2 of the License, or       *
 *    (at your option) any later version.                                     *
 *                                                                            *
 *    This program is distributed in the hope that it will be useful,         *
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *    GNU General Public License for more details.                            *
 *                                                                            *
 *****************************************************************************/

/********** And de 2 booleens *********/

#include "vrel.hpp"

#include "and.hpp"
#include "data.hpp"


// Constructeur.
And::And (Data * opgauche, Data * opdroite)
{
  ligne = yylineno;
  op_gauche = opgauche;
  op_droite = opdroite;
}

// Ex�cution.
Data* And::get_data (void)
{
  Data *opg, *opd;
  Data *resultat;

  opg = op_gauche->get_data();
  opd = op_droite->get_data();
  
  resultat = opg->And(opd);
  if (resultat == NULL) {
    cout << "Error at line " << ligne << " : not booleans\n";
    exit(1);
  }
  return resultat;
}

// Destructeur.
And::~And ()
{
  delete op_gauche;
  delete op_droite;
}
