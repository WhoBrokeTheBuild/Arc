#include "DrawableComponent.h"

const Arc::UnitComponentType Arc::DrawableComponent::UNIT_CMP_TYPE_DRAWABLE = "drawable";

const Arc::EventType Arc::DrawableComponent::EVENT_ORIGIN_CHANGED      = "drawableComponent.originChanged";
const Arc::EventType Arc::DrawableComponent::EVENT_BLEND_COLOR_CHANGED = "drawableComponent.blendColorChanged";
const Arc::EventType Arc::DrawableComponent::EVENT_ROTATION_CHANGED	   = "drawableComponent.rotationCanhged";
const Arc::EventType Arc::DrawableComponent::EVENT_SCALE_CHANGED	   = "drawableComponent.scaleChanged";
const Arc::EventType Arc::DrawableComponent::EVENT_OFFSET_CHANGED	   = "drawableComponent.offsetChanged";
