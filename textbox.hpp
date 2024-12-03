#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class Textbox
{
public:
	Textbox() {}
	Textbox(int size, sf::Color color, bool sel, std::string title)
	{
		textbox.setCharacterSize(size);
		textbox.setFillColor(color);
		isSelected = sel;
		if (sel)
			textbox.setString(">_");
		else
			textbox.setString(">");
		std::cout << title << "Text Box Created\n";
	}
	void setFont(sf::Font &font)
	{
		textbox.setFont(font);
	}
	void setPosition(sf::Vector2f pos)
	{
		textbox.setPosition(pos);
	}
	void setLimit(bool ToF)
	{
		hasLimit = ToF;
	}
	void setLimit(bool ToF, int lim)
	{
		hasLimit = ToF;
		limit = lim;
	}
	bool isSelectedBox()
	{
		return isSelected;
	}
	void setSelected(bool sel)
	{
		isSelected = sel;
		if (!sel)
		{
			std::string t = text.str();
			std::string newT = "";
			for (int i = 0; i < t.length(); i++)
			{
				newT += t[i];
			}
			textbox.setString(title + newT);
		}
	}
	std::string getText()
	{
		return text.str();
	}
	void drawTo(sf::RenderWindow &window)
	{
		window.draw(textbox);
	}
	void typedOn(sf::Event input)
	{
		if (isSelected)
		{
			int charTyped = input.text.unicode;
			if (charTyped < 128)
			{
				if (hasLimit)
				{
					if (text.str().length() <= limit)
					{
						inputLogic(charTyped);
					}
					else if (text.str().length() > limit && charTyped == DELETE_KEY)
					{
						deleteLastChar();
					}
				}
				else
				{
					inputLogic(charTyped);
				}
			}
		}
	}

private:
	sf::Text textbox;
	std::ostringstream text;
	std::string title = "";
	bool isSelected = false;
	bool hasLimit = false;
	int limit = 10;

	void inputLogic(int charTyped)
	{
		if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY)
		{
			text << static_cast<char>(charTyped);
		}
		else if (charTyped == DELETE_KEY)
		{
			if (text.str().length() > 0)
			{
				deleteLastChar();
			}
		}
		else if (charTyped == ENTER_KEY)
		{
			std::string s = text.str();
			s.append("\n");
			text.str("");
			text << s;
			textbox.setString(">" + title + text.str());
		}

		textbox.setString(">" + title + text.str() + "_");
	}

	void deleteLastChar()
	{
		std::string t = text.str();

		text.str("");
		text << t.substr(0, t.size() - 1);
		textbox.setString(">" + text.str() + "_");
	}
};