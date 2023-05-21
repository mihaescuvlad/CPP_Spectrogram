#include "NavDetails.hpp"

NavDetails::NavDetails(const TextNavDetailsConfig& currentPath, const TextNavDetailsConfig& pageCount)
{
	m_currentPath.setString(currentPath.m_text);
	m_currentPath.setCharacterSize(currentPath.m_char_size);
	m_currentPath.setFont(currentPath.m_font);
	m_currentPath.setFillColor(currentPath.m_text_color);

	updatePageText();
	m_pageText.setCharacterSize(pageCount.m_char_size);
	m_pageText.setFont(pageCount.m_font);
	m_pageText.setFillColor(pageCount.m_text_color);
}

void NavDetails::updatePageText()
{
	const std::string displayText{ std::to_string(m_currentPage) + '/' + std::to_string(m_pageCount)};

	m_pageText.setString(displayText);
}

void NavDetails::setCurrentPath(const std::unique_ptr<IFileManager>& path)
{
	m_currentPath.setString(path->getCurrentDirectory().string());

	const unsigned pageCount{ path->getFileCountInDirectory() };
	setPageCount(pageCount);

	const unsigned currentPage{ pageCount != 0 };
	setCurrentPage(currentPage);
}

void NavDetails::setCurrentPage(unsigned page)
{
	m_currentPage = page;
}

void NavDetails::setPageCount(unsigned pageCount)
{
	m_pageCount = pageCount;
}

void NavDetails::setPathPosition(const sf::Vector2f& pos)
{
	m_currentPath.setPosition(pos);
}

void NavDetails::setPagePosition(const sf::Vector2f& pos)
{
	m_pageText.setPosition(pos);
}

unsigned NavDetails::getCurrentPage() const
{
	return m_currentPage;
}

unsigned NavDetails::getPageCount() const
{
	return m_pageCount;
}

void NavDetails::drawTo(sf::RenderWindow& window) const
{
	window.draw(m_currentPath);
	window.draw(m_pageText);
}