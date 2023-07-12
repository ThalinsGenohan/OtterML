#ifndef OTER_TEXTURE2D_H
#define OTER_TEXTURE2D_H

#include <OtterML/System/Vector2.hpp>

namespace oter
{
class Texture2D
{
public:
	struct AnimationFrame;

	using Animation = std::vector<AnimationFrame>;

	Texture2D();

	void Generate(u32 width, u32 height, const u8* data);
	void Generate(const Vector2<u32>& size, const u8* data);

	void Delete();

	void Bind() const;

	u32 GetID() const;

	const Vector2<u32>& GetTextureSize() const;

	const Vector2<u32>& GetFrameSize() const;
	void                     SetFrameSize(const Vector2<u32>& frameSize);

	const std::unordered_map<std::string, Animation>& GetAnimations() const;
	void                                              SetAnimations(const std::unordered_map<std::string, Animation>& animations);

	const Animation& GetAnimation(const std::string& animationName) const;
	void             SetAnimation(const std::string& animationName, const Animation& animation);

	const AnimationFrame& GetAnimationFrame(const std::string& animationName, u32 frameNumber) const;
	void                  SetAnimationFrame(const std::string& animationName, u32 frameNumber, const AnimationFrame& frame);

private:
	u32          _id        = 0;
	Vector2<u32> _size      = Vector2<u32>(0u);
	Vector2<u32> _frameSize = Vector2<u32>(0u);

	std::unordered_map<std::string, Animation> _animations;
};

struct Texture2D::AnimationFrame
{
public:
	Vector2<u32> framePosition = Vector2<u32>(0u);
	f32             milliseconds  = 0.f;
};
}

#endif
