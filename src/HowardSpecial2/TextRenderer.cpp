#include "TextRenderer.h"
#include "Mesh.h"
#include "glm/ext.hpp"
#include "Transform.h"
#include "GameObject.h"

TextRenderer::TextRenderer(){
	quad = std::make_shared<Mesh>("../src/game/models/quad.obj"); //load a qaud
	spriteSheet = std::make_shared<Sprite>(); //create the sprite sheet
	spriteSheet->load("../src/game/textures/font.png"); //load the sprite sheet
	projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f); //create the projection matrix
	sprite_h = 46; //set the height and width of the sprited (this is dependent on the sprite sheet and shoudln't be done like this)
	sprite_w = 49;
	std::shared_ptr<Texture> letter;
	int xscale = (int)spriteSheet->GetSize().x / sprite_w; //get the amount of sprites per row
	int yscale = (int)spriteSheet->GetSize().y / sprite_h; //get the amount of sprites per colomn
	for (int i = 0; i < yscale; i++) { //create a texture for every sprite in the sheet
		for (int j = 0; j < xscale; j++) {
			letter = spriteSheet->createTextureFromSprite(sprite_w * j, sprite_h * i, sprite_w, sprite_h);
			letters.push_back(letter);
		}
	}
}

void TextRenderer::OnUpdate(){
	shader->SetUniform("in_Projection", projection); //set the projection in the shader
	glm::vec3 pos = GetGameObject()->GetTransform()->position; //get the beginning position of the text
	glm::vec3 posMod;
	for (int i = 0; i < (int)text.length(); i++) { //for every letter in the message
		char letter = text.at(i);
		switch (letter) { //the worlds biggest switch/case to check which letter we're doing (this could be done better)
		default:
			shader->SetUniform("in_Texture", letters.at(0));
		case 'A':
			shader->SetUniform("in_Texture", letters.at(0));
			break;
		case 'B':
			shader->SetUniform("in_Texture", letters.at(1));
			break;
		case 'C':
			shader->SetUniform("in_Texture", letters.at(2));
			break;
		case 'D':
			shader->SetUniform("in_Texture", letters.at(3));
			break;
		case 'E':
			shader->SetUniform("in_Texture", letters.at(4));
			break;
		case 'F':
			shader->SetUniform("in_Texture", letters.at(5));
			break;
		case 'G':
			shader->SetUniform("in_Texture", letters.at(6));
			break;
		case 'H':
			shader->SetUniform("in_Texture", letters.at(7));
			break;
		case 'I':
			shader->SetUniform("in_Texture", letters.at(8));
			break;
		case 'J':
			shader->SetUniform("in_Texture", letters.at(9));
			break;
		case 'K':
			shader->SetUniform("in_Texture", letters.at(10));
			break;
		case 'L':
			shader->SetUniform("in_Texture", letters.at(11));
			break;
		case 'M':
			shader->SetUniform("in_Texture", letters.at(12));
			break;
		case 'N':
			shader->SetUniform("in_Texture", letters.at(13));
			break;
		case 'O':
			shader->SetUniform("in_Texture", letters.at(14));
			break;
		case 'P':
			shader->SetUniform("in_Texture", letters.at(15));
			break;
		case 'Q':
			shader->SetUniform("in_Texture", letters.at(16));
			break;
		case 'R':
			shader->SetUniform("in_Texture", letters.at(17));
			break;
		case 'S':
			shader->SetUniform("in_Texture", letters.at(18));
			break;
		case 'T':
			shader->SetUniform("in_Texture", letters.at(19));
			break;
		case 'U':
			shader->SetUniform("in_Texture", letters.at(20));
			break;
		case 'V':
			shader->SetUniform("in_Texture", letters.at(21));
			break;
		case 'W':
			shader->SetUniform("in_Texture", letters.at(22));
			break;
		case 'X':
			shader->SetUniform("in_Texture", letters.at(23));
			break;
		case 'Y':
			shader->SetUniform("in_Texture", letters.at(24));
			break;
		case 'Z':
			shader->SetUniform("in_Texture", letters.at(25));
			break;
		case 'a':
			shader->SetUniform("in_Texture", letters.at(26));
			break;
		case 'b':
			shader->SetUniform("in_Texture", letters.at(27));
			break;
		case 'c':
			shader->SetUniform("in_Texture", letters.at(28));
			break;
		case 'd':
			shader->SetUniform("in_Texture", letters.at(29));
			break;
		case 'e':
			shader->SetUniform("in_Texture", letters.at(30));
			break;
		case 'f':
			shader->SetUniform("in_Texture", letters.at(31));
			break;
		case 'g':
			shader->SetUniform("in_Texture", letters.at(32));
			break;
		case 'h':
			shader->SetUniform("in_Texture", letters.at(33));
			break;
		case 'i':
			shader->SetUniform("in_Texture", letters.at(34));
			break;
		case 'j':
			shader->SetUniform("in_Texture", letters.at(35));
			break;
		case 'k':
			shader->SetUniform("in_Texture", letters.at(36));
			break;
		case 'l':
			shader->SetUniform("in_Texture", letters.at(37));
			break;
		case 'm':
			shader->SetUniform("in_Texture", letters.at(38));
			break;
		case 'n':
			shader->SetUniform("in_Texture", letters.at(39));
			break;
		case 'o':
			shader->SetUniform("in_Texture", letters.at(40));
			break;
		case 'p':
			shader->SetUniform("in_Texture", letters.at(41));
			break;
		case 'q':
			shader->SetUniform("in_Texture", letters.at(42));
			break;
		case 'r':
			shader->SetUniform("in_Texture", letters.at(43));
			break;
		case 's':
			shader->SetUniform("in_Texture", letters.at(44));
			break;
		case 't':
			shader->SetUniform("in_Texture", letters.at(45));
			break;
		case 'u':
			shader->SetUniform("in_Texture", letters.at(46));
			break;
		case 'v':
			shader->SetUniform("in_Texture", letters.at(47));
			break;
		case 'w':
			shader->SetUniform("in_Texture", letters.at(48));
			break;
		case 'x':
			shader->SetUniform("in_Texture", letters.at(49));
			break;
		case 'y':
			shader->SetUniform("in_Texture", letters.at(50));
			break;
		case 'z':
			shader->SetUniform("in_Texture", letters.at(51));
			break;
		case '0':
			shader->SetUniform("in_Texture", letters.at(52));
			break;
		case '1':
			shader->SetUniform("in_Texture", letters.at(53));
			break;
		case '2':
			shader->SetUniform("in_Texture", letters.at(54));
			break;
		case '3':
			shader->SetUniform("in_Texture", letters.at(55));
			break;
		case '4':
			shader->SetUniform("in_Texture", letters.at(56));
			break;
		case '5':
			shader->SetUniform("in_Texture", letters.at(57));
			break;
		case '6':
			shader->SetUniform("in_Texture", letters.at(58));
			break;
		case '7':
			shader->SetUniform("in_Texture", letters.at(59));
			break;
		case '8':
			shader->SetUniform("in_Texture", letters.at(60));
			break;
		case '9':
			shader->SetUniform("in_Texture", letters.at(61));
			break;
		case '.':
			shader->SetUniform("in_Texture", letters.at(62));
			break;
		case ',':
			shader->SetUniform("in_Texture", letters.at(63));
			break;
		case ';':
			shader->SetUniform("in_Texture", letters.at(64));
			break;
		case ':':
			shader->SetUniform("in_Texture", letters.at(65));
			break;
		case ' ': //if there's a space skip drawing anything
			continue;
		}

		posMod.x = (float)i * GetGameObject()->GetTransform()->scale.x * 0.5f; //move forward an amount based on the sprite and position in the message
		GetGameObject()->GetTransform()->position = pos + posMod;
		shader->SetUniform("in_Model", GetGameObject()->GetTransform()->GetModel()); //set the model matrix
		shader->Draw(quad); //draw the quad
	}
	GetGameObject()->GetTransform()->position -= posMod; //reset the position back to it's intial one
	

}

void TextRenderer::SetMesh(std::shared_ptr<Mesh> _mesh) {
	quad = _mesh;
}

void TextRenderer::SetTexture(std::shared_ptr<Texture> _texture) {
	//spriteSheet = _texture;
}

void TextRenderer::SetText(std::string _text){
	text = _text;
}
