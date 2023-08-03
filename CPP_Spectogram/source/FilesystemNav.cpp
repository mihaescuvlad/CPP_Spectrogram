#include "FilesystemNav.hpp"

#include <functional>
#include <utility>

void FilesystemNav::setNavColor(const sf::Color& color)
{
	m_tab.setFillColor(color);
}

void FilesystemNav::setTextColor(const sf::Color& pathTextColor, const sf::Color& pageTextColor)
{
	m_details.setPathColor(pathTextColor);
	m_details.setPageColor(pageTextColor);
}

void FilesystemNav::setControlColor(const sf::Color& nextPageColor, const sf::Color& prevPageColor, const sf::Color& closeTabColor)
{
	m_controls.setNextPageColor(nextPageColor);
	m_controls.setPrevPageColor(prevPageColor);
	m_controls.setCloseTabColor(closeTabColor);
}

void FilesystemNav::updateOptionsColorScheme()
{
	m_controls.updateTextures(m_tabTheme.getCurrentTheme());

	for (auto& option : m_options)
	{
		option.setBackColor(m_tabTheme.getPButtonColor());
		option.setTextColor(m_tabTheme.getTextColor());
	}
}

//void FilesystemNav::updateOptionPositions()
//{
//	const auto [startPos, endPos] = m_details.getCurrentPageRange();
//	const auto fileCount = m_options.size();
//
//	for (size_t optionIterator = startPos; optionIterator < endPos && optionIterator < fileCount; ++optionIterator)
//	{
//		if (isFirstOptionOnPage(optionIterator))
//		{
//			m_options.at(optionIterator).setPosition(m_firstOptionPosition);
//			continue;
//		}
//
//		sf::Vector2f newPosition = m_options.at(optionIterator - 1).getPosition();
//		newPosition.y += m_options.at(optionIterator - 1).getHeight() + 15;
//		m_options.at(optionIterator).setPosition(newPosition);
//	}
//}

//void FilesystemNav::updateOptionPositions()
//{
//	// TODO: Use std::view::enumerate when C++23 comes out
//	const auto workingRange = getCurrentPageWorkingRange();
//
//	//const auto firstElement = getCurrentPageWorkingRange().begin();
//	const auto firstElement = std::ranges::begin(workingRange);
//
//	firstElement->setPosition(m_firstOptionPosition);
//
//	workingRange.begin() = std::next(workingRange.begin());
//
//	auto& previousOption = *firstElement;
//
//	for (auto& option : workingRange)
//	{
//		sf::Vector2f newPosition = previousOption.getPosition();
//		newPosition.y += previousOption.getHeight() + 15;
//		
//		option.setPosition(newPosition);
//		
//		previousOption = option;
//	}
//}

void FilesystemNav::updateOptionPositions()
{
	// TODO: Use std::view::enumerate when C++23 comes out
	const auto workingRange = getCurrentPageWorkingRange();

	TextButton previousElement = *workingRange.begin();

	bool isFirst = true;
	for(auto& option : workingRange)
	{
		if(isFirst)
		{
			option.setPosition(m_firstOptionPosition);
			previousElement = option;

			isFirst = false;
			continue;
		}

		sf::Vector2f newPosition = previousElement.getPosition();
		newPosition.y += previousElement.getHeight() + 15;
	
		option.setPosition(newPosition);
		previousElement = option;
	}
}

void FilesystemNav::updateOptions()
{
	m_options.clear();

	m_options.emplace_back(m_optionConfig.m_size, m_tabTheme.getPButtonColor(), "..",
		m_optionConfig.m_char_size, m_optionConfig.m_font, m_tabTheme.getTextColor());

	for (auto& option : m_fileManager->getFilesInCurrentDirectory())
	{
		std::string optionString = processOptionString(option.string());
		m_options.emplace_back(m_optionConfig.m_size, m_tabTheme.getPButtonColor(), optionString,
			m_optionConfig.m_char_size, m_optionConfig.m_font, m_tabTheme.getTextColor());
	}
}

std::string FilesystemNav::getLastPart(const std::string& inputString)
{
	const std::size_t lastDelimiterPos = (inputString.find_last_of('\\') != std::string::npos) ? inputString.find_last_of('\\') : inputString.find_last_of('/');
	std::string lastPart;

	if (lastDelimiterPos != std::string::npos)
	{
		lastPart = inputString.substr(lastDelimiterPos + 1);
	}
	else
	{
		lastPart = inputString;
	}

	return lastPart;
}

std::string FilesystemNav::textWraparound(const std::string& inputString)
{
	std::string processedString = inputString;

	if (processedString.length() > Constants::MAX_CHARACTERS_PER_ROW)
	{
		processedString.insert(Constants::MAX_CHARACTERS_PER_ROW, "\n");
	}

	return processedString;
}

std::string FilesystemNav::textAddEllipsis(const std::string& inputString)
{
	std::string processedString = inputString;

	if (processedString.length() > Constants::MAX_CHARACTERS_TIL_ELLIPSING)
	{
		processedString.resize(Constants::MAX_CHARACTERS_TIL_ELLIPSING);
		processedString += "...";
	}

	return processedString;
}

std::string FilesystemNav::processOptionString(const std::string& inputString)
{
	std::string processedString = getLastPart(inputString);
	processedString = textWraparound(processedString);
	processedString = textAddEllipsis(processedString);

	return processedString;
}

FilesystemNav::const_range FilesystemNav::getCurrentPageWorkingRange() const
{
	return getCurrentPageWorkingRangeImpl(*this);
}

FilesystemNav::range FilesystemNav::getCurrentPageWorkingRange()
{
	return getCurrentPageWorkingRangeImpl(*this);
}

FilesystemNav::const_range FilesystemNav::makePageWorkingRange(const_range_it begin, const_range_it end)
{
	return {std::move(begin), std::move(end)};
}

FilesystemNav::range FilesystemNav::makePageWorkingRange(range_it begin, range_it end)
{
	return {std::move(begin), std::move(end)};
}

bool FilesystemNav::isFirstOptionOnPage(const size_t optionIterator) const
{
	const size_t firstOnPage = (static_cast<size_t>(m_details.getCurrentPage()) - 1) * Constants::MAX_NAV_ELEMENT_COUNT;
	return optionIterator == firstOnPage;
}

void FilesystemNav::changePath(const std::filesystem::path& newPath)
{
	if(newPath == "..") {
		m_fileManager->updateDirectory(m_fileManager->getParentForCurrentPath());
		m_details.setCurrentPath(m_fileManager);

		return;
	}

	if (std::filesystem::status(m_fileManager->getCurrentDirectory()).type() == std::filesystem::file_type::not_found)
	{
		return;
	}

	if (is_regular_file(newPath))
	{
		if (!newPath.has_extension() || Constants::SUPPORTED_FILE_EXTENSIONS.count(newPath.extension().string()) <= 0) return;

		m_spectrogram.setFilePath(newPath);
    m_currentFileText.setString(getLastPart(newPath.string()));
    m_displayNav = false;
  }
	else if (is_directory(newPath))
	{
		m_fileManager->updateDirectory(newPath);
		m_details.setCurrentPath(m_fileManager);
	}
}

void FilesystemNav::updateColors()
{
	m_optionConfig.m_bg_color = m_tabTheme.getPButtonColor();
	m_optionConfig.m_color = m_tabTheme.getTextColor();

	updateOptionsColorScheme();

	setNavColor(m_tabTheme.getSButtonColor());
	setTextColor(m_tabTheme.getTextColor(), m_tabTheme.getTextColor());
	setControlColor(m_tabTheme.getPButtonColor(), m_tabTheme.getPButtonColor(), m_tabTheme.getPButtonColor());
}

void FilesystemNav::setTheme(const GuiTheme& newTheme)
{
	m_tabTheme = newTheme;

	updateColors();
}

void FilesystemNav::setDetailsPosition(const sf::Vector2f& posPath, const sf::Vector2f& posPage)
{
	m_details.setPathPosition(posPath);
	m_details.setPagePosition(posPage);
}

void FilesystemNav::setControlsPosition(const sf::Vector2f& posNextPage, const sf::Vector2f& posPrevPage, const sf::Vector2f& posCloseTab)
{
	m_controls.setControlsPosition(posNextPage, posPrevPage, posCloseTab);
}

bool FilesystemNav::isMouseOverNextPage(const sf::RenderWindow& window)
{
	if(m_controls.isMouseOverNextPage(window))
	{
		m_controls.setNextPageColor(m_tabTheme.getAccentColor());

		return true;
	}

	m_controls.setNextPageColor(m_tabTheme.getPButtonColor());
	return false;
}

bool FilesystemNav::isMouseOverPrevPage(const sf::RenderWindow& window)
{
	if (m_controls.isMouseOverPrevPage(window))
	{
		m_controls.setPrevPageColor(m_tabTheme.getAccentColor());

		return true;
	}

	m_controls.setPrevPageColor(m_tabTheme.getPButtonColor());
	return false;
}

bool FilesystemNav::isMouseOverCloseTab(const sf::RenderWindow& window)
{
	if (m_controls.isMouseOverCloseTab(window))
	{
		m_controls.setCloseTabColor(m_tabTheme.getAccentColor());

		return true;
	}

	m_controls.setCloseTabColor(m_tabTheme.getPButtonColor());
	return false;
}

//bool FilesystemNav::isMouseOverOption(const sf::RenderWindow& window)
//{
//	const auto [startPos, endPos] = m_details.getCurrentPageRange();
//	const auto fileCount = static_cast<size_t>(m_options.size());
//
//	for (size_t optionIterator = startPos; optionIterator < endPos && optionIterator < fileCount; ++optionIterator)
//	{
//		if (m_options.at(optionIterator).isMouseOver(window))
//		{
//			m_options.at(optionIterator).setBackColor(m_tabTheme.getAccentColor());
//
//			return true;
//		}
//		else
//		{
//			m_options.at(optionIterator).setBackColor(m_tabTheme.getPButtonColor());
//		}
//	}
//
//	return false;
//}

bool FilesystemNav::isMouseOverOption(const sf::RenderWindow& window)
{
	for (auto& option : getCurrentPageWorkingRange())
	{
		if (option.isMouseOver(window))
		{
			option.setBackColor(m_tabTheme.getAccentColor());

			return true;
		}
		else
		{
			option.setBackColor(m_tabTheme.getPButtonColor());
		}
	}

	return false;
}

void FilesystemNav::pressNextPage()
{
	m_details.incrementPage();
	updateOptionPositions();
}

void FilesystemNav::pressPrevPage()
{
	m_details.decrementPage();
	updateOptionPositions();
}

void FilesystemNav::pressCloseTab()
{
	m_details.setCurrentPage(1);
	updateOptionPositions();
}

void FilesystemNav::pressOption(const sf::RenderWindow& window)
{
	const auto [startPos, endPos] = m_details.getCurrentPageRange();
	const auto fileCount = m_options.size();

	for (size_t optionIterator = startPos; optionIterator < endPos && optionIterator < fileCount; ++optionIterator)
	{
		if (!m_options.at(optionIterator).isMouseOver(window))
		{
			continue;
		}

		if (m_options.at(optionIterator).getString() == "..") 
		{
			changePath("..");
		}
		else
		{
			std::string filePath = m_fileManager->getFile(optionIterator - 1).string();
			changePath(filePath);
		}

	}

	updateOptions();
	updateOptionPositions();
}


//void FilesystemNav::displayElementsOnPage(sf::RenderWindow& window) const
//{
//	// TODO: Make it use Iterators
//	const auto [startPos, endPos] = m_details.getCurrentPageRange();
//	const auto fileCount = m_options.size();
//	const auto maxPos = std::min(endPos, fileCount);
//	const auto length = maxPos - startPos;
//
//	//for (size_t optionIterator = startPos; optionIterator < endPos && optionIterator < fileCount; ++optionIterator)
//	//{
//	//	// TODO: Print the "Ellipsis" output
//	//	m_options.at(optionIterator).drawTo(window);
//	//}
//
//	//for (const auto& option : m_options | std::ranges::subrange(it1, it2))
//	for(const auto& option : std::views::counted(m_options.begin() + static_cast<long long>(startPos), static_cast<long long>(length)))
//	{
//		option.drawTo(window);
//	}
//}

void FilesystemNav::displayElementsOnPage(sf::RenderWindow& window) const
{
	for (const auto& option : getCurrentPageWorkingRange())
	{
		option.drawTo(window);
	}
}

void FilesystemNav::drawTo(sf::RenderWindow& window) const
{
	window.draw(m_tab);

	displayElementsOnPage(window);

	m_details.drawTo(window);
	m_controls.drawTo(window);
}
