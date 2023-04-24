#include "Stat.h"
#include "Event.h"
#include "TexteSaisie.h"
#include "Texte_A_Recopier.h"

using namespace sf;
using namespace std;

Texte_A_Recopier::Texte_A_Recopier(Font &font)
{
	text_.setString("");
	text_.setFont(font);
	text_.setCharacterSize(32);
	text_.setFillColor(Color::White);
	text_.setPosition(200, 400);
}

void Texte_A_Recopier::setText(String a) 
{
	text_.setString(a);
}

void Texte_A_Recopier::afficher(RenderWindow &window) {
	window.draw(text_);
}