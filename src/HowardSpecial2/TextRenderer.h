#pragma once
#include "Component.h"
#include <memory>
#include "ShaderProgram.h"

struct Mesh;
struct Sprite;
/**
 * a component for rendering text on the screen
 */
struct TextRenderer : public Component {
	TextRenderer(); ///< constructor
	void OnUpdate();
	int sprite_h; ///< height of each sprite in the sprite sheet
	int sprite_w; ///< width of each sprite in the sprite sheet
	void SetMesh(std::shared_ptr<Mesh> _mesh); ///< set the mesh (should just be a quad)
	void SetTexture(std::shared_ptr<Texture> _texture); ///< set the texture (should be a sprite sheet)
	void SetText(std::string _text); ///< set the string to be drawn to screen

private:
	std::shared_ptr<ShaderProgram> shader = std::make_shared<ShaderProgram>("../shaders/spriteshader.vert", "../shaders/spriteshader.frag"); ///< shader used to draw the object
	std::shared_ptr<Mesh> quad; ///< the mesh
	std::shared_ptr<Sprite> spriteSheet; ///< the sprite sheet

	std::string text; ///< the text to be drawn on screen
	std::vector<std::shared_ptr<Texture>> letters; ///< a list of textures, each one being a letter
	glm::mat4 projection; ///< text projection matrix
	
};