/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <string>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <librevenge-stream/librevenge-stream.h>

#include "PropertyID.h"

namespace libone
{

PropertyID::PropertyID(uint32_t new_value)
{
  val = new_value;
}

uint32_t PropertyID::get_value()
{
  return val;
}

uint32_t PropertyID::get_id()
{
  return val & 0x3FFFFFF;
}

uint32_t PropertyID::get_type()
{
  return (val & 0x7C000000) >> 26;
}

uint16_t PropertyID::get_bool_value()
{
  /* TODO: this could be converted to return a real boolean */
  return (uint16_t) ((val & 0x80000000) >> 31);
}



std::string PropertyID::type_to_string()
{
  switch (get_type())
  {
  case NoData:
    return "NoData";
  case Bool:
    return "Bool";
  case OneByteOfData:
    return "OneByteOfData";
  case TwoBytesOfData:
    return "TwoBytesOfData";
  case FourBytesOfData:
    return "FourBytesOfData";
  case EightBytesOfData:
    return "EightBytesOfData";
  case FourBytesOfLengthFollowedByData:
    return "FourBytesOfLengthFollowedByData";
  case ObjectID:
    return "ObjectID";
  case ArrayOfObjectIDs:
    return "ArrayOfObjectIDs";
  case ObjectSpaceID:
    return "ObjectSpaceID";
  case ArrayOfObjectSpaceIDs:
    return "ArrayOfObjectSpaceIDs";
  case ContextID:
    return "ContextID";
  case ArrayOfContextIDs:
    return "ArrayOfContextIDs";
  case ArrayOfPropertyValues:
    return "ArrayOfPropertyValues";
  case PropertySet:
    return "PropertySet";
  case property_NIL:
  default:
    return "unknown type";

  }
}

std::string PropertyID::value_to_string()
{
  std::stringstream stream;
  stream << std::hex;
  switch (get_value())
  {
  case LayoutTightLayout:
    stream << "LayoutTightLayout";
    break;
  case PageWidth:
    stream << "PageWidth";
    break;
  case PageHeight:
    stream << "PageHeight";
    break;
  case OutlineElementChildLevel:
    stream << "OutlineElementChildLevel";
    break;
  case Bold:
    stream << "Bold";
    break;
  case Italic:
    stream << "Italic";
    break;
  case Underline:
    stream << "Underline";
    break;
  case Strikethrough:
    stream << "Strikethrough";
    break;
  case Superscript:
    stream << "Superscript";
    break;
  case Subscript:
    stream << "Subscript";
    break;
  case Font:
    stream << "Font";
    break;
  case FontSize:
    stream << "FontSize";
    break;
  case FontColor:
    stream << "FontColor";
    break;
  case Highlight:
    stream << "Highlight";
    break;
  case RgOutlineIndentDistance:
    stream << "RgOutlineIndentDistance";
    break;
  case BodyTextAlignment:
    stream << "BodyTextAlignment";
    break;
  case OffsetFromParentHoriz:
    stream << "OffsetFromParentHoriz";
    break;
  case OffsetFromParentVert:
    stream << "OffsetFromParentVert";
    break;
  case NumberListFormat:
    stream << "NumberListFormat";
    break;
  case LayoutMaxWidth:
    stream << "LayoutMaxWidth";
    break;
  case LayoutMaxHeight:
    stream << "LayoutMaxHeight";
    break;
  case ContentChildNodesOfOutlineElement:
    stream << "ContentChildNodesOf--";
    break;
  case ElementChildNodesOfVersionHistory:
    stream << "ElementChildNodesOfVersionHistory";
    break;
  case EnableHistory:
    stream << "EnableHistory";
    break;
  case RichEditTextUnicode:
    stream << "RichEditTextUnicode";
    break;
  case ListNodes:
    stream << "ListNodes";
    break;
  case NotebookManagementEntityGuid:
    stream << "NotebookManagementEntityGuid";
    break;
  case OutlineElementRTL:
    stream << "OutlineElementRTL";
    break;
  case LanguageID:
    stream << "LanguageID";
    break;
  case LayoutAlignmentInParent:
    stream << "LayoutAlignmentInParent";
    break;
  case PictureContainer:
    stream << "PictureContainer";
    break;
  case PageMarginTop:
    stream << "PageMarginTop";
    break;
  case PageMarginBottom:
    stream << "PageMarginBottom";
    break;
  case PageMarginLeft:
    stream << "PageMarginLeft";
    break;
  case PageMarginRight:
    stream << "PageMarginRight";
    break;
  case ListFont:
    stream << "ListFont";
    break;
  case TopologyCreationTimeStamp:
    stream << "TopologyCreationTimeStamp";
    break;
  case LayoutAlignmentSelf:
    stream << "LayoutAlignmentSelf";
    break;
  case IsTitleTime:
    stream << "IsTitleTime";
    break;
  case IsBoilerText:
    stream << "IsBoilerText";
    break;
  case PageSize:
    stream << "PageSize";
    break;
  case PortraitPage:
    stream << "PortraitPage";
    break;
  case EnforceOutlineStructure:
    stream << "EnforceOutlineStructure";
    break;
  case EditRootRTL:
    stream << "EditRootRTL";
    break;
  case CannotBeSelected:
    stream << "CannotBeSelected";
    break;
  case IsTitleText:
    stream << "IsTitleText";
    break;
  case IsTitleDate:
    stream << "IsTitleDate";
    break;
  case ListRestart:
    stream << "ListRestart";
    break;
  case IsLayoutSizeSetByUser:
    stream << "IsLayoutSizeSetByUser";
    break;
  case ListSpacingMu:
    stream << "ListSpacingMu";
    break;
  case LayoutOutlineReservedWidth:
    stream << "LayoutOutlineReservedWidth";
    break;
  case LayoutResolveChildCollisions:
    stream << "LayoutResolveChildCollisions";
    break;
  case IsReadOnly:
    stream << "IsReadOnly";
    break;
  case LayoutMinimumOutlineWidth:
    stream << "LayoutMinimumOutlineWidth";
    break;
  case LayoutCollisionPriority:
    stream << "LayoutCollisionPriority";
    break;
  case CachedTitleString:
    stream << "CachedTitleString";
    break;
  case DescendantsCannotBeMoved:
    stream << "DescendantsCannotBeMoved";
    break;
  case RichEditTextLangID:
    stream << "RichEditTextLangID";
    break;
  case LayoutTightAlignment:
    stream << "LayoutTightAlignment";
    break;
  case Charset:
    stream << "Charset";
    break;
  case CreationTimeStamp:
    stream << "CreationTimeStamp";
    break;
  case Deletable:
    stream << "Deletable";
    break;
  case ListMSAAIndex:
    stream << "ListMSAAIndex";
    break;
  case IsBackground:
    stream << "IsBackground";
    break;
  case IRecordMedia:
    stream << "IRecordMedia";
    break;
  case CachedTitleStringFromPage:
    stream << "CachedTitleStringFromPage";
    break;
  case RowCount:
    stream << "RowCount";
    break;
  case ColumnCount:
    stream << "ColumnCount";
    break;
  case TableBordersVisible:
    stream << "TableBordersVisible";
    break;
  case StructureElementChildNodes:
    stream << "StructureElementChildNodes";
    break;
  case ChildGraphSpaceElementNodes:
    stream << "ChildGraphSpaceElementNodes";
    break;
  case TableColumnWidths:
    stream << "TableColumnWidths";
    break;
  case Author:
    stream << "Author";
    break;
  case LastModifiedTimeStamp:
    stream << "LastModifiedTimeStamp";
    break;
  case AuthorOriginal:
    stream << "AuthorOriginal";
    break;
  case AuthorMostRecent:
    stream << "AuthorMostRecent";
    break;
  case LastModifiedTime:
    stream << "LastModifiedTime";
    break;
  case IsConflictPage:
    stream << "IsConflictPage";
    break;
  case TableColumnsLocked:
    stream << "TableColumnsLocked";
    break;
  case SchemaRevisionInOrderToRead:
    stream << "SchemaRevisionInOrderToRead";
    break;
  case IsConflictObjectForRender:
    stream << "IsConflictObjectForRender";
    break;
  case EmbeddedFileContainer:
    stream << "EmbeddedFileContainer";
    break;
  case EmbeddedFileName:
    stream << "EmbeddedFileName";
    break;
  case SourceFilepath:
    stream << "SourceFilepath";
    break;
  case ConflictingUserName:
    stream << "ConflictingUserName";
    break;
  case ImageFilename:
    stream << "ImageFilename";
    break;
  case IsConflictObjectForSelection:
    stream << "IsConflictObjectForSelection";
    break;
  case PageLevel:
    stream << "PageLevel";
    break;
  case TextRunIndex:
    stream << "TextRunIndex";
    break;
  case TextRunFormatting:
    stream << "TextRunFormatting";
    break;
  case Hyperlink:
    stream << "Hyperlink";
    break;
  case UnderlineType:
    stream << "UnderlineType";
    break;
  case Hidden:
    stream << "Hidden";
    break;
  case HyperlinkProtected:
    stream << "HyperlinkProtected";
    break;
  case TextRunIsEmbeddedObject:
    stream << "TextRunIsEmbeddedObject";
    break;
  case ImageAltText:
    stream << "ImageAltText";
    break;
  case MathFormatting:
    stream << "MathFormatting";
    break;
  case ParagraphStyle:
    stream << "ParagraphStyle";
    break;
  case ParagraphSpaceBefore:
    stream << "ParagraphSpaceBefore";
    break;
  case ParagraphSpaceAfter:
    stream << "ParagraphSpaceAfter";
    break;
  case ParagraphLineSpacingExact:
    stream << "ParagraphLineSpacingExact";
    break;
  case MetaDataObjectsAboveGraphSpace:
    stream << "MetaDataObjectsAboveGraphSpace";
    break;
  case TextRunDataObject:
    stream << "TextRunDataObject";
    break;
  case TextRunData:
    stream << "TextRunData";
    break;
  case ParagraphStyleId:
    stream << "ParagraphStyleId";
    break;
  case HasVersionPages:
    stream << "HasVersionPages";
    break;
  case ActionItemType:
    stream << "ActionItemType";
    break;
  case NoteTagShape:
    stream << "NoteTagShape";
    break;
  case NoteTagHighlightColor:
    stream << "NoteTagHighlightColor";
    break;
  case NoteTagTextColor:
    stream << "NoteTagTextColor";
    break;
  case NoteTagPropertyStatus:
    stream << "NoteTagPropertyStatus";
    break;
  case NoteTagLabel:
    stream << "NoteTagLabel";
    break;
  case NoteTagCreated:
    stream << "NoteTagCreated";
    break;
  case NoteTagCompleted:
    stream << "NoteTagCompleted";
    break;
  case NoteTagDefinitionOid:
    stream << "NoteTagDefinitionOid";
    break;
  case NoteTagStates:
    stream << "NoteTagStates";
    break;
  case ActionItemStatus:
    stream << "ActionItemStatus";
    break;
  case ActionItemSchemaVersion:
    stream << "ActionItemSchemaVersion";
    break;
  case ReadingOrderRTL:
    stream << "ReadingOrderRTL";
    break;
  case ParagraphAlignment:
    stream << "ParagraphAlignment";
    break;
  case VersionHistoryGraphSpaceContextNodes:
    stream << "VersionHistoryGraphSpaceContextNodes";
    break;
  case DisplayedPageNumber:
    stream << "DisplayedPageNumber";
    break;
  case SectionDisplayName:
    stream << "SectionDisplayName";
    break;
  case NextStyle:
    stream << "NextStyle";
    break;
  case WebPictureContainer2398:
    stream << "WebPictureContainer2398";
    break;
  case value_NIL:
    stream << "NIL";
    break;
  default:
    stream << get_value();
    break;
  }
  return stream.str();
}

std::string PropertyID::to_string()
{
  std::stringstream stream;
  stream << std::hex << "PropertyID " << value_to_string() << " id " << get_id() << " " << type_to_string() << " bool " << get_bool_value();
  return stream.str();
}
}
