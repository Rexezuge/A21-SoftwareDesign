# Create contact ABC in group abc
curl -v -X POST localhost:3001/contacts/abc/ABC -H "Content-Type:application/json" -d '{"phone": 123, "email": "example.com"}'
# Should be 406
sleep 1
# Get groups
curl -v -X GET localhost:3001/groups
# Should be null
sleep 1

# Create group abv, abvd
curl -v -X POST localhost:3001/groups/abc
curl -v -X POST localhost:3001/groups/abcd
# Should be 201

# Get groups
curl -v -X GET localhost:3001/groups
# Should return json

# Create contact ABC in abc, ABCD in abcd
curl -v -X POST localhost:3001/contacts/abc/ABC -H "Content-Type:application/json" -d '{"phone": 123, "email": "example.com"}'
curl -v -X POST localhost:3001/contacts/abcd/ABCD -H "Content-Type:application/json" -d '{"phone": 123, "email": "example.com"}'
# Should be 201

# Create contact ABCD in abc
curl -v -X POST localhost:3001/contacts/abc/ABCD -H "Content-Type:application/json" -d '{"phone": 123, "email": "example.com"}'
# Should be 410

# Get contact ABCD in abc
curl -v -X GET localhost:3001/contacts/abc/ABCD
# Should be 404

# Move contact ABCD to abc
curl -v -X PATCH localhost:3001/groups/abcd/ABCD/abc
# Should be 200

# Move contact ABCD to abc
curl -v -X PATCH localhost:3001/groups/abcd/ABCD/abc
# Should be 406

# Delete contact ABCD
curl -v -X DELETE localhost:3001/contacts/abc/ABCD
# Should be 200
