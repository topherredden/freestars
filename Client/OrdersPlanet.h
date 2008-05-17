/*
Copyright 2005 Elliott Kleinrock

This file is part of FreeStars, a free clone of the Stars! game.

FreeStars is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

FreeStars is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with FreeStars; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

The full GPL Copyright notice should be in the file COPYING.txt

Contact:
Email Elliott at 9jm0tjj02@sneakemail.com
*/

/** \file OrdersPlanet.h
 * \brief Planet Orders window
 * \ingroup Client
 */

#if !defined(OrdersPlanet_h)
#define OrdersPlanet_h


class OrdersPlanet: public wxPanel
{
public:
    OrdersPlanet(MainWindow * parent, wxWindow * frame);
	virtual ~OrdersPlanet();

	void SetLocation(FreeStars::Planet * planet);

private:
	MainWindow * mMainWindow;
	wxWindow * mFrame;

    DECLARE_EVENT_TABLE()
};

#endif // OrdersPlanet_h
