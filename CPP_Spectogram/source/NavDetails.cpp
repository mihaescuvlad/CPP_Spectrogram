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

unsigned NavDetails::computePageCount(unsigned fileCount)
{
	const unsigned maxPerPage = Constants::MAX_NAV_ELEMENT_COUNT;
	unsigned pageCount = fileCount / maxPerPage;

	if(fileCount % maxPerPage != 0)
	{
		++pageCount;
	}

	return pageCount;
}

std::string NavDetails::shortenPath(const std::unique_ptr<IFileManager>&path)
{
	std::string shortenedPath = path->getCurrentDirectory().string();

	if (shortenedPath.length() > Constants::MAX_PATH_LENGTH)
	{
		shortenedPath.resize(Constants::MAX_PATH_LENGTH);
		shortenedPath += "...";
	}

	return shortenedPath;
}

void NavDetails::setCurrentPath(const std::unique_ptr<IFileManager>& path)
{
	m_currentPath.setString(shortenPath(path));

	const unsigned fileCount{ path->getFileCountInDirectory() + 1 };
	const unsigned pageCount{ computePageCount(fileCount) };
	setPageCount(pageCount);

	setCurrentPage(1);

	updatePageText();
}

void NavDetails::setCurrentPage(unsigned page)
{
	m_currentPage = page;
	updatePageText();
}

void NavDetails::setPageCount(unsigned pageCount)
{
	m_pageCount = pageCount;
	updatePageText();
}

void NavDetails::incrementPage()
{
	if(m_currentPage < m_pageCount)
	{
		++m_currentPage;
		updatePageText();
	}
}

void NavDetails::decrementPage()
{
	if (m_currentPage > 1)
	{
		--m_currentPage;
		updatePageText();
	}
}

void NavDetails::setPathColor(const sf::Color& color)
{
	m_currentPath.setFillColor(color);
}

void NavDetails::setPageColor(const sf::Color& color)
{
	m_pageText.setFillColor(color);
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

std::pair<size_t, size_t> NavDetails::getCurrentPageRange() const
{
	const size_t startPos = static_cast<size_t>(m_currentPage - 1) * Constants::MAX_NAV_ELEMENT_COUNT;
	const size_t endPos = startPos + Constants::MAX_NAV_ELEMENT_COUNT;

	return { startPos, endPos };
}

void NavDetails::drawTo(sf::RenderWindow& window) const
{
	window.draw(m_currentPath);
	window.draw(m_pageText);
}