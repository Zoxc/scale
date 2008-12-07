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

#include "Graphics.hpp"
#include "ListSearch.hpp"

namespace Scale
{
    ListSearch::ListSearch(List* AOwner):
        Element::Element((Element*)AOwner),
        Owner(AOwner),
        Count(0)
    {
        Owner->OnItemCreate = OnItemCreate;
        Owner->OnItemFree = OnItemFree;

        Owner->OnItemAllocate = OnItemAllocate;
        Owner->OnItemDeallocate = OnItemDeallocate;

        Owner->Tag = (void*)this;

        Search = "";
    }

    ListSearch::~ListSearch()
    {
    }

    void ListSearch::SetCount(int NewCount)
    {
        Count = NewCount;

        Filter();
    }

    void ListSearch::Allocate()
    {
        Element::Allocate();
    }

    void ListSearch::Deallocate()
    {
        Element::Deallocate();
    }

    void ListSearch::Filter()
    {
        if(Search == "")
        {
            Owner->SetCount(Count);

            for(int i = 0; i < Count; i++)
            {
                ListSearchItem* Data = (ListSearchItem*)Owner->Items[i].Data;

                Data->Index = i;
                Data->Caption = OnString(this, i);
            }
        }
        else
        {
            int ListCount = 0;

            // Count result
            for(int i = 0; i < Count; i++)
                if(strstr(OnString(this, i), Search.c_str()) != 0)
                    ListCount++;

            Owner->SetCount(ListCount);

            if(ListCount == 0)
            {
                std::string NoResult = "Could not find any results for";//: '\x0B" + Search + "\x0B'";

                //Owner->SetMessage("Could not find any results for"/*NoResult.c_str()*/);
            }
            else
            {
                int ListIndex = 0;

                std::string SearchBold = "\x0B" + Search + "\x0B";

                for(int i = 0; i < Count; i++)
                {
                    const char* Text = OnString(this, i);
                    const char* Pos = strstr(Text, Search.c_str());

                    if(Pos != 0)
                    {
                        ListSearchItem* Data = (ListSearchItem*)Owner->Items[ListIndex++].Data;

                        Data->Index = i;
                        Data->Caption = Text;
                        Data->Caption.replace((size_t)Pos - (size_t)Text, Search.length(), SearchBold);
                    }
                }
            }
        }
    }

    void ListSearch::OnItemCreate(ListItem* Item)
    {
        Item->Data = (void*)new ListSearchItem();
    }

    void ListSearch::OnItemFree(ListItem* Item)
    {
        delete (ListSearchItem*)Item->Data;
    }

    void ListSearch::OnItemAllocate(ListItem* Item)
    {
        ListSearchItem* Data = (ListSearchItem*)Item->Data;

        Item->Icon = OnImage(this, Data->Index);
        Item->Caption = Data->Caption.c_str();
    }

    void ListSearch::OnItemDeallocate(ListItem* Item)
    {
    }

    // Static callbacks

    void ListSearch::OnItemCreate(List* Owner, ListItem* Item)
    {
        ((ListSearch*)Owner->Tag)->OnItemCreate(Item);
    }

    void ListSearch::OnItemFree(List* Owner, ListItem* Item)
    {
        ((ListSearch*)Owner->Tag)->OnItemFree(Item);
    }

    void ListSearch::OnItemAllocate(List* Owner, ListItem* Item)
    {
        ((ListSearch*)Owner->Tag)->OnItemAllocate(Item);
    }

    void ListSearch::OnItemDeallocate(List* Owner, ListItem* Item)
    {
        ((ListSearch*)Owner->Tag)->OnItemDeallocate(Item);
    }
};
