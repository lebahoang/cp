import fs = require('fs')
import path = require('path')

type  TripId =  string
interface Location {
    latitude:  number,
    longitude:  number
}

enum WaypointType {
    Pickup  =  1,
    Dropoff =  2
}

interface Waypoint {
    type : WaypointType
    location: Location
}

interface Vertex {
    tripId: TripId,
    point: Waypoint
    adjacentList: number[]
    indegree: number
}

interface Trip {
    id: TripId
    pickupWaypoint: Waypoint
    dropoffWaypoint: Waypoint
}

interface WaypointOutput {
    tripId: TripId
    type : WaypointType
}


/** *
 * @param location1 Input location
 * @param location2 Input location
 * @returns Very simple crow distance between 2 points
 */
const distance = (location1: Location, location2: Location): number => {
    const dlat = (location2.latitude - location1.latitude)
    const dlon = (location2.longitude - location1.longitude)
    return Math.sqrt(dlat * dlat + dlon * dlon)
}

/** *
* @param point the Waypoint for which we need to build the key
* @returns key for this Waypoint
*/
const buildKeyForWaypoint = (point:Waypoint): string => {
    return point.location.latitude + '|' + point.location.longitude
}

/** *
* @param trips List of rider trips
* @return graph of points in format of adjacent list
*/
const buildGraph = (trips: Trip[]): Vertex[] => {
    let vertices:Vertex[] = []
    let mapVertices:{[key: string]: number} = {}
    for (let i = 0; i < trips.length; i++) {
        let dropoffKey = buildKeyForWaypoint(trips[i].dropoffWaypoint)
        if (mapVertices[dropoffKey] === undefined) {
            vertices.push({
                tripId: trips[i].id,
                point: trips[i].dropoffWaypoint,
                adjacentList: [],
                indegree: 1
            })
            mapVertices[dropoffKey] = vertices.length-1
        } else {
            let ind = mapVertices[dropoffKey]
            vertices[ind].indegree++
        }

        let pickupKey = buildKeyForWaypoint(trips[i].pickupWaypoint)
        if (mapVertices[pickupKey] === undefined) {
            vertices.push({
                tripId: trips[i].id,
                point: trips[i].pickupWaypoint,
                adjacentList: [mapVertices[dropoffKey]],
                indegree: 0
            })
            mapVertices[pickupKey] = vertices.length-1
        } else {
            let ind = mapVertices[pickupKey]
            vertices[ind].adjacentList.push(mapVertices[dropoffKey])
        }

    }
    return vertices
}

/** *
 * @param vertex a tail vertex  
 * @returns index of checkingArray from which the distance to the vertex is minimum      
 */
const findMinimumDistanceVertex = (vertex:Vertex, checkingArray:Vertex[]): number => {
    if (vertex === null) {
        return 0
    }
    let minDistance = -1
    let minInd = -1
    for (let i = 0; i < checkingArray.length; i++) {
        let d:number = distance(vertex.point.location, checkingArray[i].point.location)
        if (minDistance === -1 || minDistance > d) {
            minDistance = d
            minInd = i
        }
    }
    return minInd
}


/** *
 * @param trips List of rider trips
 * @returns List of waypoints outputs in the most efficient
 *          order (minimizing distance between locations)
 */
const execute = (trips: Trip[]): WaypointOutput[] => {
    /* TODO fill in code here */

    // I will use Kahn algorithm to get the list of waypoint outputs
    // Kahn algorithm will satisfy the constraint pickupPoint must occur
    // before dropoffPoint
    // Time complexity: O(V+E) V: number of vertices, E: number of edges
    // Space complexisty: O(V+E) V: number of vertices, E: number of edges
    let out:WaypointOutput[] = new Array()

    let vertices = buildGraph(trips)
    let checkingArray:Vertex[] = new Array()
    let n = vertices.length
    for (let i = 0; i < n; i++) {
        if (vertices[i].indegree === 0) {
            checkingArray.push(vertices[i])
        }
    }
    let nVisited = 0
    let vertex:Vertex = null
    while (checkingArray.length > 0) {
        // in vanila implementation of Kahn algorithm, the choice of vertex is simple
        // I just pop out the vertex from stack, but because here I want to minimize the
        // distance from points hence the choice will be:
        // - finding the vertex so the distance will be minimized
        let ind:number = findMinimumDistanceVertex(vertex, checkingArray)
        vertex = checkingArray[ind]
        nVisited++
        checkingArray.splice(ind, 1)
        out.push({
            tripId: vertex.tripId,
            type : vertex.point.type
        })
        for (let i = 0; i < vertex.adjacentList.length; i++) {
            vertices[vertex.adjacentList[i]].indegree--
            if (vertices[vertex.adjacentList[i]].indegree === 0) {
                checkingArray.push(vertices[vertex.adjacentList[i]])
            }
        }
    }
    if (nVisited < n) {
        console.log('trips cannot be scheduled because there is a cycle')
        return []
    }
    return out
}

/** *
* print details of scheduled trips
* this function is useful to read the output of algorithm
* @trips Trips needed to schedule
* @waypointOuts output of the algorithm
*/
const printScheduledTrips = (trips:Trip[], waypointOuts:WaypointOutput[]) => {
    let map:{[tripId:string]:Trip} = {}
    for (let i = 0; i < trips.length; i++) {
        map[trips[i].id] = trips[i]
    }
    let points:Waypoint[] = new Array()
    for (let i = 0; i < waypointOuts.length; i++) {
        let trip:Trip = map[waypointOuts[i].tripId]
        if (trip !== undefined) {
            if (waypointOuts[i].type === WaypointType.Pickup) {
                points.push(trip.pickupWaypoint)
            } else {
                points.push(trip.dropoffWaypoint)
            }
        }
    }
    console.log(JSON.stringify(points))
}

/** *
* read the testcases from file then execute the algorithm
* to schedule the trips for each testcase
* testcases file format is:
* - the first line is an integer N denote number of testcases
*   following is N testcases,each testcase contains
*   <M: number of trips>
*   following by M lines denote trip_id, pickup_point, dropoff_point in format
*   <trip_id>,<pickuppoint_latitude>,<pickuppoint_longitude>,<dropoffpoint_latitude>,<dropoffpoint_longitude>
*   
*
*   Testcase coule be found in 2 files small.txt and large.txt
*/
const runTestcases = () => {
    let testFile:string = process.argv[2]
    let filePath:string = path.join(__dirname, testFile)
    let data:string = fs.readFileSync(filePath).toString()
    let lines:string[] = data.split('\n')
    let nTestcases:number = parseInt(lines[0], 10)

    let c = 1
    for (let i = 0; i < nTestcases; i++) {
        let trips:Trip[] = new Array()
        let nTrips:number = parseInt(lines[c], 10)
        c++
        for (let j = 0; j < nTrips; j++) {
            let trip:string[] = lines[c].split(',')
            trips.push({
                id: trip[0],
                pickupWaypoint: <Waypoint>{
                    type : WaypointType.Pickup,
                    location: <Location>{
                        latitude: parseFloat(trip[1]),
                        longitude: parseFloat(trip[2])
                    }
                },
                dropoffWaypoint: <Waypoint>{
                    type : WaypointType.Dropoff,
                    location: <Location>{
                        latitude: parseFloat(trip[3]),
                        longitude: parseFloat(trip[4])
                    }
                }
            })
            c++
        }
        let out:WaypointOutput[] = execute(trips)
        printScheduledTrips(trips, out)
        console.log('---------------------')
    }
}

runTestcases()
