/*
    Scale - An shell for Pandora, a handheld gaming device.
    Copyright (C) 2008 Zoxc

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <string>
#include "Element.hpp"
#include "List.hpp"

namespace Scale
{
    class ListSearch:
        public Element
    {
        public:
            typedef OpenGL::Texture* (*ListSearchImage)(ListSearch* Owner, int Index);
            typedef const char* (*ListSearchString)(ListSearch* Owner, int Index);

            ListSearch(List* AOwner);
            virtual ~ListSearch();

            void Allocate();
            void Deallocate();

            void Filter();

            void SetCount(int NewCount);

            struct ListSearchItem
            {
                std::string Caption;
                int Index;
            };

            std::string Search;

            List* Owner;

            ListSearchImage OnImage;
            ListSearchString OnString;

        protected:
            int Count;

            void OnItemCreate(ListItem* Item);
            void OnItemFree(ListItem* Item);
            void OnItemAllocate(ListItem* Item);
            void OnItemDeallocate(ListItem* Item);

            static void OnItemCreate(List* Owner, ListItem* Item);
            static void OnItemFree(List* Owner, ListItem* Item);
            static void OnItemAllocate(List* Owner, ListItem* Item);
            static void OnItemDeallocate(List* Owner, ListItem* Item);
    };
};
