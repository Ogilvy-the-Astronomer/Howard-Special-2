#include <HowardSpecial2/HowardSpecial2.h>
/**
 * Player controller component 
 */
struct PlayerController : public Component {
	std::shared_ptr<Keyboard> Input; ///< reference to input manager
	std::shared_ptr<GameObject> camera; ///< reference to main camera
	std::shared_ptr<Rigidbody> rb; ///< refernce to player body
	std::shared_ptr<SoundSource> audioSource;
	const float clampVal = glm::radians(70.0f); ///< camera maximum rotation amount
	void OnUpdate(float _deltaT);
	void OnStart();

};