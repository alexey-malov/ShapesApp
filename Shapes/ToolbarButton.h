#pragma once
#include "Button.h"
namespace ui
{
struct IToolbarButton
{
	typedef Signal<void()> OnClick;

	virtual void SetAction(OnClick::slot_type const &handler) = 0;

	virtual void SetIcon(const std::shared_ptr<sf::Texture> & texture) = 0;

	virtual void SetBackground(const std::shared_ptr<IImage> & image) = 0;
};


class CToolbarButton:
	public IToolbarButton
{
public:
	static std::shared_ptr<CToolbarButton> Create(std::shared_ptr<CButton> & button);
	void SetAction(OnClick::slot_type const &handler) override;
	void SetIcon(const std::shared_ptr<sf::Texture> & texture) override;
	void SetBackground(const std::shared_ptr<IImage> & image) override;

private:
	CToolbarButton(std::shared_ptr<CButton> & button);

	std::shared_ptr<CButton> m_button;
	boost::signals2::scoped_connection m_connection;

};

}