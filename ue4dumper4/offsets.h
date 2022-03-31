#pragma once

namespace Offsets {
    //Global
    extern kaddr Base;
    extern kaddr EndBase;
    extern kaddr GWorld;
    extern kaddr GWOffset;
    extern kaddr GNames;
    extern kaddr GNOffset;
    extern kaddr GUObjectArray;
    extern kaddr PointerSize;
    extern kaddr FUObjectItemPad;
    extern kaddr FUObjectItemSize;

    //---------SDK-----------//
    //---------4.23+---------//
    //Class: FNamePool
    extern kaddr FNameStride;
    extern kaddr GNamesToFNamePool;//NamePoolData, alignas(FNamePool)
    extern kaddr FNamePoolToCurrentBlock;
    extern kaddr FNamePoolToCurrentByteCursor;
    extern kaddr FNamePoolToBlocks;
    //Class: FNameEntry
    extern kaddr FNameEntryToLenBit;
    extern kaddr FNameEntryToString;
    //Class: UStruct
    extern kaddr UStructToChildProperties;
    //Class: FField
    extern kaddr FFieldToClass;
    extern kaddr FFieldToNext;
    extern kaddr FFieldToName;
    //---------4.18+---------//
    //Class: FNameEntry
    extern kaddr FNameEntryToNameString;
    //-----------------------//
    //Class: FUObjectArray
    extern kaddr FUObjectArrayToTUObjectArray;
    //Class: TUObjectArray
    extern kaddr TUObjectArrayToNumElements;
    //Class: UObject
    extern kaddr UObjectToInternalIndex;
    extern kaddr UObjectToClassPrivate;
    extern kaddr UObjectToFNameIndex;
    extern kaddr UObjectToOuterPrivate;
    //Class: UField
    extern kaddr UFieldToNext;
    //Class: UStruct
    extern kaddr UStructToSuperStruct;
    extern kaddr UStructToChildren;
    //Class: UFunction
    extern kaddr UFunctionToFunctionFlags;
    extern kaddr UFunctionToFunc;
    //Class: UProperty
    extern kaddr UPropertyToElementSize;
    extern kaddr UPropertyToPropertyFlags;
    extern kaddr UPropertyToOffsetInternal;
    //Class: UBoolProperty
    extern kaddr UBoolPropertyToFieldSize;
    extern kaddr UBoolPropertyToByteOffset;
    extern kaddr UBoolPropertyToByteMask;
    extern kaddr UBoolPropertyToFieldMask;
    //Class: UObjectProperty
    extern kaddr UObjectPropertyToPropertyClass;
    //Class: UClassProperty
    extern kaddr UClassPropertyToMetaClass;
    //Class: UInterfaceProperty
    extern kaddr UInterfacePropertyToInterfaceClass;
    //Class: UArrayProperty
    extern kaddr UArrayPropertyToInnerProperty;
    //Class: UMapProperty
    extern kaddr UMapPropertyToKeyProp;
    extern kaddr UMapPropertyToValueProp;
    //Class: USetProperty
    extern kaddr USetPropertyToElementProp;
    //Class: UStructProperty
    extern kaddr UStructPropertyToStruct;
    //Class: UWorld
    extern kaddr UWorldToPersistentLevel;
    //Class: ULevel
    extern kaddr ULevelToAActors;
    extern kaddr ULevelToAActorsCount;

    void initOffsets_32();
    void patchUE423_32();
    void patchCustom_32();
    void initOffsets_64();
    void patchUE423_64();
    void patchCustom_64();
}





