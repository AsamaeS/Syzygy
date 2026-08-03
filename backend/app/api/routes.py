from fastapi import APIRouter
from pydantic import BaseModel

router = APIRouter(prefix="/api/v1")

class BidRequest(BaseModel):
    node_id: str
    quantity: float
    price: float
    direction: str  # "buy" or "sell"

@router.post("/bids")
async def submit_bid(bid: BidRequest):
    return {"status": "recorded", "bid": bid.dict()}

@router.get("/market/mcp")
async def get_market_clearing_price():
    return {"mcp": 0.085, "currency": "USD/kWh", "timestamp": "2026-08-03T12:00:00Z"}
